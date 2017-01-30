#include <thread>
#include <iostream>
#include<stdio.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <cstdlib>

#include "communicationbuffer.h"
#include "timer.h"

CommunicationBuffer buffer;
int left_speed = 0;
int right_speed = 0;
void txLoop(void){
	std::cout << buffer.initCommunication();
	while(1){
		left_speed++;
		if(left_speed>150){
			left_speed = 0;
		}
		buffer.setDrivesSpeed(left_speed, right_speed);
		std::cout << "txLoop" << std::endl;
		std::cout << buffer.send() << std::endl;
		usleep(100000);
		buffer.receive();
		buffer.print();
	}
}

void userLoop(){
	uint16_t left_speed = 0;
	uint16_t right_speed = 0;
	char c;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while(1){
		std::cin.get(c);
		switch(c){
			case 'q':{
				return;
			}
			case '1':{
				buffer.setRelay1(true);
				break;
			}
			case '2':{
				buffer.setRelay2(true);
				break;
			}
			case '3':{
				buffer.setRelay3(true);
				break;
			}
			case '4':{
				buffer.setRelay4(true);
				break;
			}
			case '!':{
				buffer.setRelay1(false);
				break;
			}
			case '@':{
				buffer.setRelay2(false);
				break;
			}
			case '#':{
				buffer.setRelay3(false);
				break;
			}
			case '$':{
				buffer.setRelay4(false);
				break;
			}
			case 'f':{
				if(left_speed < 100){
					++left_speed;
				}
				buffer.setDrivesSpeed(left_speed, right_speed);
				break;
			}
			case 'j':{
				if(right_speed < 100){
					++right_speed;
				}
				buffer.setDrivesSpeed(left_speed, right_speed);
				break;
			}
			case 'v':{
				if(left_speed > -100){
					++left_speed;
				}
				buffer.setDrivesSpeed(left_speed, right_speed);
				break;
			}
			case 'n':{
				if(right_speed > -100){
					++right_speed;
				}
				buffer.setDrivesSpeed(left_speed, right_speed);
				break;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc == 3){
		left_speed = atoi(argv[1]);
		right_speed = atoi(argv[2]);
	}
	std::thread userThread(userLoop);
	std::thread txThread(txLoop);
	userThread.join();
	txThread.join();
	return 0;
}
