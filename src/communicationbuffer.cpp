#include "communicationbuffer.h"

CommunicationBuffer::CommunicationBuffer(){
	this->txFrame.relays = 0;
	this->txFrame.timestamp = 0;
	this->txFrame.left_speed = 0;
	this->txFrame.right_speed = 0;
	this->txFrame.shutdown = 0;
}

CommunicationBuffer::~CommunicationBuffer(){
}

void CommunicationBuffer::setDrivesSpeed(int8_t left, int8_t right){
	std::lock_guard<std::mutex> lock(txMutex);
	this->txFrame.left_speed = left;
	this->txFrame.right_speed = right;
}

void CommunicationBuffer::setSound(SOUNDS s){
	std::lock_guard<std::mutex> lock(txMutex);
	this->txFrame.sound = (uint8_t)s;
}

void CommunicationBuffer::setRelay1(bool b){
	this->helpRelays(0, b);
}

void CommunicationBuffer::setRelay2(bool b){
	this->helpRelays(1, b);
}

void CommunicationBuffer::setRelay3(bool b){
	this->helpRelays(2, b);
}

void CommunicationBuffer::setRelay4(bool b){
	this->helpRelays(3, b);
}

void CommunicationBuffer::setShutdown(uint8_t time_sec){
	std::lock_guard<std::mutex> lock(txMutex);
	this->txFrame.shutdown = time_sec;
}

bool CommunicationBuffer::isPressedButton1(){
	return this->helpButtons(0);
}

bool CommunicationBuffer::isPressedButton2(){
	return this->helpButtons(1);
}

bool CommunicationBuffer::isPressedButton3(){
	return this->helpButtons(2);
}

bool CommunicationBuffer::isPressedButton4(){
	return this->helpButtons(3);
}

int32_t CommunicationBuffer::getLeftDrivePosition(){
	std::lock_guard<std::mutex> lock(rxMutex);
	return this->rxFrame.left_position;
}

int32_t CommunicationBuffer::getRightDrivePosition(){
	std::lock_guard<std::mutex> lock(rxMutex);
	return this->rxFrame.right_position;
}

uint16_t CommunicationBuffer::getBatteryMiliV(){
	std::lock_guard<std::mutex> lock(rxMutex);
	return this->rxFrame.battery*10;
}

ERRORS CommunicationBuffer::getError(){
	return NO_ERROR;
}

void CommunicationBuffer::print(){
	this->txMutex.lock();
	std::cout << "DRIVES SPEED:\tL:" << (int)(this->txFrame.left_speed) << "\t R:" << (int)(this->txFrame.right_speed) << std::endl;
	std::cout << "RELAYS ON:";
	for (int i = 0; i < 4; ++i)
	{
		if (this->txFrame.relays & (0x01 << i))
		{
			std:: cout << " " << i+1;
		}
	}
	std::cout << std::endl;
	std::cout << "SOUND: " << this->txFrame.sound << "\t SHUTDOWN: " << this->txFrame.shutdown << std::endl;
	this->txMutex.unlock(); 

	this->rxMutex.lock();
	std::cout << "DRIVES POSITION:\tL:" << this->rxFrame.left_position << "\t R:" << this->rxFrame.right_position << std::endl;
	std::cout << "BUTTON PRESSED:";
	for (int i = 0; i < 4; ++i)
	{
		if(this->rxFrame.buttons & (0x01 << i)){
			std::cout << " " << i+1;
		}
	}
	std::cout << std::endl << "BATTERY[V]:\t" << this->rxFrame.battery/100.0 << std::endl;
	this->rxMutex.unlock();
}

void CommunicationBuffer::controllEvent(){
	std::cout << "controllEvent" << std::endl;
}

int CommunicationBuffer::send(){
	char frame[FRAME_LEN];
	int ret = 0;

	this->txMutex.lock();
	uint64_t timestamp = this->fill_timestamp(this->txFrame);
	int frame_size = this->create_hdlc_frame(frame+1, this->txFrame);
	this->txMutex.unlock();


	frame[0] = 0x7e;
	frame_size++;
	std::cout <<this->txFrame.left_speed << " "<< frame_size << "frame\n";
	for(int i = 0; i < SEND_REPEAT; i++){
		int write_return = write(this->uart_desc, frame, frame_size);
		if(write_return <= 0){
			ret--;
		}else{
			ret = write_return;
		}
	}
	if (ret > -SEND_REPEAT){
		tx_timestamps_set.insert(timestamp);
	}
	return ret;
}

int CommunicationBuffer::receive(){
	char rx[BUFFER_LEN];
	int read_return = read(this->uart_desc, rx, sizeof rx);
	int i = 0;
	while(i < read_return){
		rx_data.push(rx[i]);
		i++;
	}

	int messages_count = 0;

	while(!rx_data.empty()){
		char got_message = true;
		unsigned int message_length = 0;
		RxFrame package;
		yahdlc_control_t control_recv;
		char c;
		c = rx_data.front();
		rx_data.pop();
		rx_global_buffer[rx_global_iterator] = c;
		rx_global_iterator++;
		if(rx_global_iterator > MESSAGE_BUFFER_LEN){
			rx_global_iterator = 0;
		}

		yahdlc_get_data(&control_recv, rx_global_buffer, rx_global_iterator, (char*)(&package), &message_length);
		got_message = (message_length == sizeof(RxFrame));

		if(got_message){
			auto tx_iter = tx_timestamps_set.find(package.timestamp);
			if(tx_iter != tx_timestamps_set.end()){
				//rx_packages.push(DataRx(package, control_recv.seq_no & 0x7e, (control_recv.seq_no >> 7) & 0x1));
				//tx_timestamps_set.erase(tx_iter);
				std::cout << "received" << package.timestamp << std::endl;
				this->rxMutex.lock();
				this->rxFrame = package;
				this->rxMutex.unlock();
			}
			//rx_packages.push(DataRx(package, control_recv.seq_no & 0x7e, (control_recv.seq_no >> 7) & 0x1));
			rx_global_iterator = 0;
			messages_count++;
		}
	}
	return messages_count;
}

int CommunicationBuffer::initCommunication(){
	char *portname = "/dev/ttyS0";
	this->uart_desc = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (this->uart_desc < 0){
		error_message ("error %d opening %s: %s");
		return -1;
	}
	int err = set_interface_attribs(this->uart_desc, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	if (err < 0){
		err -= 10;
		return err;
	}
	err = set_blocking (this->uart_desc, 0);                // set no blocking
	if (err < 0){
		err -= 20;
		return err;
	}
	return this->uart_desc;
}

void CommunicationBuffer::txEvent(){
	std::cout << "sending:" << std::endl;
	this->send();
}

void CommunicationBuffer::rxEvent(){
	std::cout << "receiving" << std::endl;
	this->receive();
	controllEvent();
}

void CommunicationBuffer::helpRelays(uint8_t no, bool on){
	std::lock_guard<std::mutex> lock(txMutex);
	if (on)
	{
		this->txFrame.relays |= 0x01 << no;
	}else
	{
		this->txFrame.relays &= ~(0x01 << no);
	}
}

bool CommunicationBuffer::helpButtons(uint8_t no){
	std::lock_guard<std::mutex> lock(rxMutex);
	bool ret = (rxFrame.buttons & 0x01 << no);
	return ret;
}

int CommunicationBuffer::create_hdlc_frame(char* frame, TxFrame &package){
	yahdlc_control_t control;
	// Initialize the control field structure with frame type and sequence number
	control.frame = YAHDLC_FRAME_DATA;
	// Create an empty frame with the control field information
	unsigned frame_length;
	yahdlc_frame_data(&control, (char *)(&package), sizeof(TxFrame), frame, &frame_length);
	return frame_length;
}

unsigned CommunicationBuffer::fill_timestamp(TxFrame &package){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	package.timestamp = tv.tv_usec + 1000000*tv.tv_sec;
	return package.timestamp;
}

double CommunicationBuffer::get_ping_pong_time(TxFrame & package){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned int ret = tv.tv_usec + 1000000*tv.tv_sec - package.timestamp;
	return ret/1000.0;
}

void CommunicationBuffer::error_message(char * string){
	cout << string << errno << endl;
}
int CommunicationBuffer::set_interface_attribs (int fd, int speed, int parity){
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
			error_message ("error %d from tcgetattr");
			return -1;
	}
	cfsetospeed (&tty, speed);
	cfsetispeed (&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
									// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 0;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
									// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
			error_message ("error %d from tcsetattr");
			return -2;
	}
	return 0;
}

int CommunicationBuffer::set_blocking (int fd, int should_block)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
			error_message ("error %d from tggetattr");
			return -1;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0){
		error_message ("error %d setting term attributes");
		return -1;
	}
	return 0;
}
