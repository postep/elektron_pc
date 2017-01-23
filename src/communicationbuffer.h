#ifndef COMMUNICATION_BUFFER_H
#define COMMUNICATION_BUFFER_H 

#include <mutex>
#include <thread>
#include <iostream>


typedef struct 
{
	uint32_t timestamp;
	uint16_t left_speed;
	uint16_t right_speed;
	uint8_t relays;
	uint8_t sound;
	uint8_t shutdown;
}TxFrame;

typedef struct
{
	uint16_t buttons;
	double left_position;
	double right_position;
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
	void setDrivesSpeed(uint16_t left, uint16_t right);
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
	double getLeftDrivePosition();
	double getRightDrivePosition();
	uint16_t getBatteryMiliV();
	ERRORS getError();
	void print();
	void controllEvent();
	int initCommunication();
	
private:
	TxFrame txFrame;
	RxFrame rxFrame;
	std::mutex txMutex;
	std::mutex rxMutex;
	int sendStruct();
	int receiveStruct();	
	std::thread txThread;
	std::thread rxThread;
	void txEvent();
	void rxEvent();
	void helpRelays(uint8_t no, bool on);
	bool helpButtons(uint8_t no);
};

#endif
