/*
 * IrReceiver.h
 *
 *  Created on: 2019-02-24
 *      Author: pi
 */

#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

#include "Timer.h"

void ISR_Handler(void);
void IrReceiver_TimerFunc(void* p);

//https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol

class IrReceiver {

	enum RsvState
	{
		RS_None,
		RS_9msPulse,
		RS_4p5msPulse,
		RS_Done
	};


	int _nIrReceiver_pin;
	RsvState _rsvState;

	Timer _timer1;

	chrono::system_clock::time_point _startTime ;
	chrono::system_clock::time_point _endTime ;

public:

	static IrReceiver* g_pIrReceiver;

	IrReceiver();
	virtual ~IrReceiver();

	void Init();

	void Init_IO();
	void Start();
	void Stop();
	void Run();
	void Process_ISR_Handler();
	void TimerHelper();
};

#endif /* IRRECEIVER_H_ */
