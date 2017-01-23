#include "communicationbuffer.h"

CommunicationBuffer::CommunicationBuffer(){

}

CommunicationBuffer::~CommunicationBuffer(){
}

void CommunicationBuffer::setDrivesSpeed(uint16_t left, uint16_t right){
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

double CommunicationBuffer::getLeftDrivePosition(){
	std::lock_guard<std::mutex> lock(rxMutex);
	return this->rxFrame.left_position;
}

double CommunicationBuffer::getRightDrivePosition(){
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
	std::cout << "DRIVES SPEED:\tL:" << this->txFrame.left_speed << "\t R:" << this->txFrame.right_speed << std::endl;
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

int CommunicationBuffer::sendStruct(){

}

int CommunicationBuffer::receiveStruct(){

}

int CommunicationBuffer::initCommunication(){
	
}

void CommunicationBuffer::txEvent(){
	std::cout << "sending:" << std::endl;
}

void CommunicationBuffer::rxEvent(){
	std::cout << "receiving" << std::endl;
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
