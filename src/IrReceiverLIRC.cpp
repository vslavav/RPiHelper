/*
 * IrReceiverLIRC.cpp
 *
 *  Created on: 2019-02-26
 *      Author: pi
 */

#include "IrReceiverLIRC.h"
#include <lirc/lirc_client.h>
#include "GlobalDef.h"

//http://ozzmaker.com/how-to-control-the-gpio-on-a-raspberry-pi-with-an-ir-remote/

IrReceiverLIRC::IrReceiverLIRC() {
	// TODO Auto-generated constructor stub

}

IrReceiverLIRC::~IrReceiverLIRC() {
	// TODO Auto-generated destructor stub
}

void IrReceiverLIRC::Init()
{
	_IsStopCommanded = false;
	struct lirc_config *config;
	int nRes = lirc_init("lirc",1);
	if(nRes == -1)
	{
		cout << "lirc_init error " << endl;
	}

	if(lirc_readconfig(NULL,&config,NULL)!=0)
	{
		//in dir /etc/lirc create empty file "lircrc" : sudo touch lircrc
		cout << "lirc_readconfig error " << endl;
	}
}

void IrReceiverLIRC::Init_IO()
{

}

void IrReceiverLIRC::Run()
{
	const auto cycleTime = std::chrono::milliseconds(400);
	char* pCode;

	while(_IsStopCommanded == false)
	{
		chrono::high_resolution_clock::time_point startCyclePoint = chrono::high_resolution_clock::now();
		 //Do stuff while LIRC socket is open  0=open  -1=closed.
		if( lirc_nextcode(&pCode) !=0 )
		{
			break;
		}

		if(pCode == NULL)
		{
			continue;
		}

		cout << "code = " << pCode << endl;




		chrono::high_resolution_clock::time_point endCyclePoint = startCyclePoint + cycleTime;
		this_thread::sleep_until(endCyclePoint);
	}
}

void IrReceiverLIRC::Start()
{
	thread t(&IrReceiverLIRC::Run, this);

	t.detach();
}

void IrReceiverLIRC::Stop()
{
	_IsStopCommanded= true;
}

