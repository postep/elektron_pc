#ifndef COMMUNICATION_BUFFER_H
#define COMMUNICATION_BUFFER_H 

#include <mutex>
#include <thread>
#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include <queue>
#include <set>


#include "math.h"
#include "yahdlc/C/yahdlc.h"


#define FRAME_LEN 64
#define BUFFER_LEN 128
#define MESSAGE_BUFFER_LEN 64
#define SEND_REPEAT 3

using namespace std;


typedef struct 
{
	uint32_t timestamp;
	int8_t left_speed;
	int8_t right_speed;
	uint8_t relays;
	uint8_t sound;
	uint8_t shutdown;
}TxFrame;

typedef struct
{
	uint32_t timestamp;
	uint16_t buttons;
	int32_t left_position;
	int32_t right_position;
	uint16_t battery;
	uint8_t error;
}RxFrame;

enum SOUNDS
{
	NO_SOUND,
	FIRST_SOUND,
	SECOND_SOUND
};

enum ERRORS
{
	NO_ERROR
};

class CommunicationBuffer{
public:
	CommunicationBuffer();
	~CommunicationBuffer();
	void setDrivesSpeed(int8_t left, int8_t right);
	void setSound(SOUNDS s);
	void setRelay1(bool b);
	void setRelay2(bool b);
	void setRelay3(bool b);
	void setRelay4(bool b);
	void setShutdown(uint8_t time_sec);
	bool isPressedButton1();
	bool isPressedButton2();
	bool isPressedButton3();
	bool isPressedButton4();
	int32_t getLeftDrivePosition();
	int32_t getRightDrivePosition();
	uint16_t getBatteryMiliV();
	ERRORS getError();
	void print();
	void controllEvent();
	int initCommunication();
	int send();
	int receive();
	
private:
	TxFrame txFrame;
	RxFrame rxFrame;
	std::mutex txMutex;
	std::mutex rxMutex;

	int uart_desc;
	std::thread txThread;
	std::thread rxThread;
	void txEvent();
	void rxEvent();
	void helpRelays(uint8_t no, bool on);
	bool helpButtons(uint8_t no);
	int create_hdlc_frame(char* frame, TxFrame &package);
	unsigned fill_timestamp(TxFrame &package);
	double get_ping_pong_time(TxFrame & package);
	queue <char> rx_data;
	char rx_global_buffer[MESSAGE_BUFFER_LEN];
	int rx_global_iterator = 0;
	char rx_first = 0;
	std::set <uint64_t> tx_timestamps_set;
	int set_interface_attribs (int fd, int speed, int parity);
	int set_blocking (int fd, int should_block);
	void error_message(char * string);
};

#endif
