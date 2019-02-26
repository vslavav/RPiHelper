/*
 * USonicSensor.cpp
 *
 *  Created on: 2019-02-11
 *      Author: pi
 */

#include "USonicSensor.h"
#include <wiringPi.h>
#include "GlobalDef.h"

//http://codelectron.com/measure-distance-ultrasonic-sensor-pi-hc-sr04/

USonicSensor::USonicSensor() : _distance{0.0}
{
	// TODO Auto-generated constructor stub

}

USonicSensor::~USonicSensor() {
	// TODO Auto-generated destructor stub
}

void USonicSensor::Init()
{
	_distance = 0.0;
	_IsStopCommanded = false;
	_IsMeasuringDone = true;

	Init_IO();
}



void USonicSensor::Init_IO()
{
	_nTrigger_pin = 4;
	pinMode(_nTrigger_pin, OUTPUT);
	_nEcho_pin = 5;
	pinMode(_nEcho_pin, INPUT);
}

void USonicSensor::Start()
{
	thread t(&USonicSensor::Run, this);

	t.detach();
}

void USonicSensor::Run()
{
	const auto cycleTime = std::chrono::milliseconds(10);
	while(_IsStopCommanded == false)
	{
		chrono::system_clock::time_point startCyclePoint = chrono::system_clock::now();

		MeasureDistance();


		chrono::system_clock::time_point endCyclePoint = startCyclePoint + cycleTime;
		this_thread::sleep_until(endCyclePoint);
	}
}

void USonicSensor::Start_MeasureDistance()
{
	_listValues.clear();
	_IsMeasuringDone = false;
}

void USonicSensor::Stop_MeasureDistance()
{

}

void USonicSensor::ProcessValues()
{
	sort(_listValues.begin(),_listValues.end());
	double dMean = 0.0;
	int nSize = _listValues.size() / 2;
	//for(double dVal : _listValues)
	for(int ii = 0; ii < nSize; ii++)
	{

		dMean += _listValues[ii];
	}
	dMean = dMean / nSize;
	cout << ": " << dMean;
	cout << endl;

	_distance = dMean;
}

void USonicSensor::MeasureDistance()
{
	if(_IsMeasuringDone == true)
	{
		return;
	}

	digitalWrite (_nTrigger_pin, HIGH) ;
	this_thread::sleep_for(chrono::microseconds(10));
	digitalWrite (_nTrigger_pin, LOW) ;

	while(1)
	{
		int nVal = digitalRead(_nEcho_pin);
		if(nVal == 1)
		{
			break;
		}
	}
	chrono::system_clock::time_point startTime = chrono::high_resolution_clock::now();
	while(1)
	{
		int nVal = digitalRead(_nEcho_pin);
		if(nVal == 0)
		{
			break;
		}
	}
	chrono::system_clock::time_point endTime = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> delta_time_milli = chrono::duration<double, milli>(endTime - startTime);
	//cout << "usonic duration = " << delta_time_milli.count() <<endl;


	double dValue = delta_time_milli.count() * 17.150; //
	//std::cout << "USonicSensor pdistance = " << _distance << " sm." << endl;
	_listValues.push_back(dValue);

	if(_listValues.size() == 6)
	{
		ProcessValues();
		_IsMeasuringDone = true;

	}


}

void USonicSensor::Stop()
{
	_IsStopCommanded = true;
}

double USonicSensor::GetDistance()
{


	return _distance;
}

