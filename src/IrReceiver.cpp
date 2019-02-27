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

	int nErr = wiringPiISR(_nIrReceiver_pin, INT_EDGE_FALLING, &ISR_Handler);

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
	cout << "IrReceiver::TimerHelper count= " <<  _nDebugCnt << endl;

	_nDebugCnt = 0;
}

void IrReceiver::Init_IO()
{
	_nIrReceiver_pin = 2;
}

void IrReceiver::Process_ISR_Handler()
{

	static bool isStart = true;

	if(_nDebugCnt == 0)
	{
		cout << "Starting timer ..."  << endl;
		_timer1.Start();
	}

	_nDebugCnt++;
	cout << "Ir Rec:counts=" << _nDebugCnt << endl;


	if(isStart == true)
	{
		isStart = false;
		_startTime = chrono::high_resolution_clock::now();

	}
	else
	{
		isStart = true;
		_endTime = chrono::high_resolution_clock::now();
		chrono::duration<double, micro> delta_time_micro = chrono::duration<double, micro>(_endTime - _startTime);
		cout << "ir duration = " << delta_time_micro.count() <<endl;
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

