/*
 * ServoSg90Control.cpp
 *
 *  Created on: 2019-02-12
 *      Author: pi
 */

#include "ServoSg90Control.h"
#include "UdpClient.h"
#include "TopMgr.h"
#include <wiringPi.h>
#include "GlobalDef.h"

//full cycle is about 20 ms
//1 ms - Zero degree
//1.5 ms - 90 degree
//2 ms = 180 degree

ServoSg90Control::ServoSg90Control() {
	// TODO Auto-generated constructor stub

}

ServoSg90Control::~ServoSg90Control() {
	// TODO Auto-generated destructor stub
}

void ServoSg90Control::Init()
{
	Init_IO();
	_IsStopCommanded = false;
	_nPositionDegree = 90;
}

void ServoSg90Control::Init_IO()
{
	_nServoPwmControl_pin = 0; // GPIO 17
	pinMode(_nServoPwmControl_pin, OUTPUT);
}

void ServoSg90Control::Start()
{
	thread t(&ServoSg90Control::Run, this);

	t.detach();
}

void ServoSg90Control::Stop()
{

}

chrono::microseconds  ServoSg90Control::ConvertPositionDegreeToDuration()
{
	//Convert the Angle to 500mks (0 degree)-2480mks (180 degree) pulse width
	//y = ax + b
	// b = 500
	// a = 11
	int nDutyTime = 500 + 11 * _nPositionDegree;
	auto dutyTime = chrono::microseconds(nDutyTime);


	return dutyTime;
}

void ServoSg90Control::Run()
{
	const auto cycleTime = std::chrono::milliseconds(20);



	UdpClient* pUdpClient = TopMgr::_pTopMgr->GetUdpClient();
	while(_IsStopCommanded == false)
	{
		chrono::high_resolution_clock::time_point startCyclePoint = chrono::high_resolution_clock::now();
		auto dutyTime = ConvertPositionDegreeToDuration();
		pUdpClient->SendMessage("ServoSg90Control::Run");
		digitalWrite (_nServoPwmControl_pin, HIGH) ;
		this_thread::sleep_for(dutyTime);
		digitalWrite (_nServoPwmControl_pin, LOW) ;



		chrono::high_resolution_clock::time_point endCyclePoint = startCyclePoint + cycleTime;
		this_thread::sleep_until(endCyclePoint);
	}
}

