/*
 * TopMgr.cpp

 *
 *  Created on: 2019-01-14
 *      Author: pi
 */

#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <iostream>

#include "TopMgr.h"
#include "StdIOMgr.h"
#include "GpioMgr.h"
#include "UdpClient.h"
#include "UdpSrv.h"


using namespace std;

TopMgr* TopMgr::_pTopMgr = nullptr;

TopMgr::TopMgr() {
	TopMgr::_pTopMgr = this;

}

TopMgr::~TopMgr() {
	// TODO Auto-generated destructor stub
}

void TopMgr::Init()
{
	_pStdIOMgr = new StdIOMgr();
	_pStdIOMgr->Init();
	_pGpioMgr = new GpioMgr();
	_pGpioMgr->Init();
	_pUdpClient = new UdpClient();
	_pUdpClient->Init();
	_pUdpSrv = new UdpSrv();
	_pUdpSrv->Init();



}

void TopMgr::Run()
{
	const auto cycleTime = std::chrono::milliseconds(100);

	_pUdpClient->SendMessage("hello from c++ rpi");

	while(1)
	{

		chrono::system_clock::time_point startPoint = chrono::system_clock::now();

		_pStdIOMgr->Run();

		if(_pStdIOMgr->IsCommandedExit() == true)
		{
			break;
		}

		string sMsgFromSrv = _pUdpSrv->GetMessage();
		if(sMsgFromSrv.empty() == false)
		{
			//_pUdpClient->SendMessage(sMsgFromSrv);
			ProceeedCmdFromUdp(sMsgFromSrv);
		}



		chrono::system_clock::time_point endPointPoint = startPoint + cycleTime;
		this_thread::sleep_until(endPointPoint);


	}

	cout << "finished" << endl;
}

void TopMgr::ProceeedCmdFromStdIo(string sCmd)
{

}

static int nVal = 0;

void TopMgr::ProceeedCmdFromUdp(string sCmd)
{

	if(sCmd == "Start UsbCam")
	{

		_pGpioMgr->SetMotorA_SpeedAsPwmValue(nVal);
		cout << "Pwm = " << nVal << endl;
		nVal++;
	}
	else if(sCmd == "Stop UsbCam")
	{
		if(nVal > 0)
		{
			nVal--;
		}
		cout << "Pwm = " << nVal << endl;
		_pGpioMgr->SetMotorA_SpeedAsPwmValue(nVal);
	}
}

