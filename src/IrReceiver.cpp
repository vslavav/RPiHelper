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
	_rsvState = RS_None;

	Init_IO();

	_nBitsCount = 0;

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


	Process();

}

void IrReceiver::Process()
{
	int nInputValue =  digitalRead(_nIrReceiver_pin);
	//cout << "Input pin value = " << nInputValue << endl;

	switch(_rsvState)
	{
	case RS_None:
		if(nInputValue == 0)
		{
			_startTime = chrono::system_clock::now();
			_rsvState = RS_9msPulse;
			_nBitsCount = 0;
		}
		break;
	case RS_9msPulse:
		if(nInputValue == 1)
		{
			_endTime = chrono::system_clock::now();
			chrono::duration<double, micro> delta_time_micro = chrono::duration<double, micro>(_endTime - _startTime);
			int duration_value = (int)delta_time_micro.count();
			if(abs(duration_value - 9000) < 900)
			{
				cout << "9ms Start pulse found-> " << duration_value <<endl;
				_rsvState = RS_4p5msPulse;
				_startTime = chrono::system_clock::now();
			}

		}

		break;
	case RS_4p5msPulse:
		if(nInputValue == 0)
		{
			_endTime = chrono::system_clock::now();
			chrono::duration<double, micro> delta_time_micro = chrono::duration<double, micro>(_endTime - _startTime);
			int duration_value = (int)delta_time_micro.count();
			if(abs(duration_value - 4500) < 450)
			{
				cout << "4.5ms Start pulse found-> " << duration_value <<endl;
				_rsvState = RS_Address;
				_nAddress = 0;
				_startTime = chrono::system_clock::now();
			}
		}
		break;

	case RS_Address:
	{
		if(nInputValue == 0)
		{
			int nDataBit = ProcessDataBits();
			_nBitsCount++;
			if(_nBitsCount > 7)
			{
				_rsvState = RS_AddressInverse;
				_nBitsCount = 0;
				cout << "Getting Address Invert "  <<endl;
			}

		}

		break;
	}

	case RS_AddressInverse:
	{

		if(nInputValue == 0)
		{
			int nDataBit = ProcessDataBits();
			_nBitsCount++;
			if(_nBitsCount > 7)
			{
				_rsvState = RS_AddressInverse;
				_nBitsCount = 0;
				cout << "Getting Address Invert "  <<endl;
			}


			_nBitsCount++;
			if(_nBitsCount > 7)
			{
				_nBitsCount = 0;
				_rsvState = RS_Done;
			}
		}
		break;
	}

	case RS_Command:
	{
		break;
	}

	case RS_CommandInverse:
	{
		break;
	}

	case RS_Done:
		break;
	}
}

int  IrReceiver::ProcessDataBits()
{
	int nBitValue = 0;
	_endTime = chrono::system_clock::now();
	chrono::duration<double, micro> delta_time_micro = chrono::duration<double, micro>(_endTime - _startTime);
	int duration_value = (int)delta_time_micro.count();
	if(duration_value > 1800 && abs(duration_value - 2250) < 450)
	{
		cout << "Address 1 pulse found-> " << duration_value <<endl;
		//_rsvState = RS_Address;
		_startTime = chrono::system_clock::now();
		nBitValue = 1;
	}
	else if(abs(duration_value - 1250) < 250)
	{
		cout << "Address 0 pulse found-> " << duration_value <<endl;
		//_rsvState = RS_Address;
		_startTime = chrono::system_clock::now();
	}
	else
	{
		_startTime = chrono::system_clock::now();
		cout << "Address Unknown pulse found-> " << duration_value <<endl;
	}

	return nBitValue;
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

