/*
 * IrReceiver.cpp
 *
 *  Created on: 2019-02-24
 *      Author: pi
 */

#include "IrReceiver.h"
#include <wiringPi.h>
#include "GlobalDef.h"



void ISR_Handler(void)
{

	if(IrReceiver::g_pIrReceiver != nullptr)
	{
		IrReceiver::g_pIrReceiver->Process_ISR_Handler();
	}
}

IrReceiver::IrReceiver() {
	// TODO Auto-generated constructor stub

}

IrReceiver::~IrReceiver() {
	// TODO Auto-generated destructor stub
}

IrReceiver* IrReceiver::g_pIrReceiver = nullptr;

void IrReceiver::Init()
{
	g_pIrReceiver = this;
	_nDebugCnt = 0;

	Init_IO();

	wiringPiISR(_nIrReceiver_pin, INT_EDGE_BOTH, &ISR_Handler);
	pinMode(_nIrReceiver_pin, INPUT);

	//set oneshot timer
	_timer1.SetTimerType(TimerType::OneShot);
	_timer1.SetInterval(200); // 100 msec
	_timer1.SetCallBack(bind(IrReceiver_TimerFunc,(void*)this));


}

void IrReceiver_TimerFunc(void* p)
{
	IrReceiver* pIrReceiver = static_cast<IrReceiver*> (p);
	pIrReceiver->TimerHelper();
}

void IrReceiver::TimerHelper()
{

}

void IrReceiver::Init_IO()
{
	_nIrReceiver_pin = 2;
}

void IrReceiver::Process_ISR_Handler()
{
	static bool isStart = false;
	static bool isFirstPulseFound = false;

	int nInputValue =  digitalRead(_nIrReceiver_pin);
	cout << "Input pin value = " << nInputValue << endl;

	if(isFirstPulseFound == false)
	{
		if(isStart == false)
		{
			if(nInputValue == 0)
			{
				_startTime = chrono::system_clock::now();
				isStart = true;
			}

		}
		else if(isStart == true)
		{
			if(nInputValue == 1)
			{
				_endTime = chrono::system_clock::now();
				isFirstPulseFound = true;
				chrono::duration<double, micro> delta_time_micro = chrono::duration<double, micro>(_endTime - _startTime);
				cout << "pulse duration = " << delta_time_micro.count() <<endl;
			}
		}
	}








}

void IrReceiver::Start()
{

}

void IrReceiver::Stop()
{

}

void IrReceiver::Run()
{

}

