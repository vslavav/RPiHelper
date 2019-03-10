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
// sony sirc proto: https://www.sbprojects.net/knowledge/ir/sirc.php

class IrReceiver {

	enum RsvState
	{
		RS_None,
		RS_9msPulse,
		RS_4p5msPulse,
		RS_Address,
		RS_AddressInverse,
		RS_Command,
		RS_CommandInverse,
		RS_FinalPulse1,
		RS_FinalPulse2,
		RS_Done
	};


	int _nIrReceiver_pin;
	RsvState _rsvState;

	int _nBitsCount;
	unsigned char _ucAddress;
	unsigned char _ucAddressInvert;
	unsigned char _ucCommand;
	unsigned char _ucCommandInvert;

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
	void Process();
	int  ProcessDataBits();
	void TimerHelper();
};

#endif /* IRRECEIVER_H_ */
