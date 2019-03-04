/*
 * GpioMgr.cpp
 *
 *  Created on: 2019-01-19
 *      Author: pi
 */

#include "GpioMgr.h"
#include <thread>
#include <iostream>
#include <cstdlib>

#include <wiringPi.h>
#include <softPwm.h>  /* include header file for software PWM */
#include "USonicSensor.h"
#include "ServoSg90Control.h"
#include "IrReceiver.h"
#include "IrReceiverLIRC.h"

using namespace std;

void ManageIO(GpioMgr* pGpioMgr)
{
	//pGpioMgr->ManagePWM();
}

GpioMgr::GpioMgr():_pServoSg90Control{nullptr}
{
	// TODO Auto-generated constructor stub

}

GpioMgr::~GpioMgr() {
	// TODO Auto-generated destructor stub
}

void GpioMgr::Init()
{
	wiringPiSetup() ;
	InitPins();


	Init_PWM();

	_timer1.SetInterval(1000); // 1 sec
	_timer1.SetCallBack(bind(TimerFunc,(void*)this));

	//_timer1.Start();

	StopMotorA();

	_pUSonicSensor = new USonicSensor();
	_pUSonicSensor->Init();
	_pUSonicSensor->Start();

	_pServoSg90Control = new ServoSg90Control();
	_pServoSg90Control->Init();
//	_pServoSg90Control->Start();

	_pIrReceiver = new IrReceiver();
	_pIrReceiver->Init();

	//_pIrReceiverLIRC = new IrReceiverLIRC();
	//_pIrReceiverLIRC->Init();
	//_pIrReceiverLIRC->Start();


//	thread t(ManageIO, this);
//	t.detach();

}

void TimerFunc(void* p)
{
	GpioMgr* pGpioMgr = static_cast<GpioMgr*> (p);
	pGpioMgr->TimerHelper();
}

void GpioMgr::TimerHelper()
{
	//cout << "GpioMgr::TimerHelper" << endl;
	static int nPositionDegree = 0;
	static bool isDir_0To180 = true;

	//_pServoSg90Control->SetPositionDegree(nPositionDegree);
	if(isDir_0To180)
	{
		nPositionDegree += 10;
		if(nPositionDegree == 170)
		{
			isDir_0To180 = false;
		}
	}
	else
	{
		nPositionDegree -= 10;
		if(nPositionDegree == 0)
		{
			isDir_0To180 = true;
		}
	}


	//_pUSonicSensor->Start_MeasureDistance();



	//cout << "PositionDegree = " << nPositionDegree << endl;
	cout << "Gpio Mgr timer ...  " << endl;
}

void GpioMgr::InitPins()
{
	//assign board pins
	_PWM_MotorA_pin = 1;          /* GPIO1 as per WiringPi,GPIO18 as per BCM */
	pinMode(_PWM_MotorA_pin, OUTPUT);	/* set GPIO as output */

	_LogicControl1_MotorA_pin = 4;   /* GPIO4 as per WiringPi,GPIO23 as per BCM */
	pinMode(_LogicControl1_MotorA_pin, OUTPUT);	/* set GPIO as output */
	_LogicControl2_MotorA_pin = 5;    /* GPIO5 as per WiringPi,GPIO24 as per BCM */
	pinMode(_LogicControl2_MotorA_pin, OUTPUT);	/* set GPIO as output */

	//assign board pins
	_PWM_MotorB_pin = 0;          /* GPIO0 as per WiringPi,GPIO17 as per BCM */
//	pinMode(_PWM_MotorB_pin, OUTPUT);	/* set GPIO as output */

	_LogicControl1_MotorB_pin = 2;   /* GPIO2 as per WiringPi,GPIO27 as per BCM */
//	pinMode(_LogicControl1_MotorB_pin, OUTPUT);	/* set GPIO as output */
	_LogicControl2_MotorB_pin = 3;    /* GPIO3 as per WiringPi,GPIO22 as per BCM */
//	pinMode(_LogicControl2_MotorB_pin, OUTPUT);	/* set GPIO as output */





}

//https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c
void GpioMgr::Init_PWM()
{

	softPwmCreate(_PWM_MotorA_pin, 1, 100);	/* set PWM channel along with range*/
	SetMotorA_PWM(0);






}

void GpioMgr::SetMotorA_PWM(int nValue)
{

	softPwmWrite (_PWM_MotorA_pin, nValue); /* change the value of PWM */

/*	unique_lock<std::mutex> lock(_mutex4cond_var);
	_cond_var.notify_one(); */
}

/*void GpioMgr::ManagePWM()
{
	unique_lock<std::mutex> lock(_mutex4cond_var);
	while(1)
	{
		_cond_var.wait(lock);
		cout << "ManagePWM ..." << endl;
		softPwmWrite (_PWM_MotorA_pin, _PWM_MotorA_value);


}} */

int GpioMgr::ConvertSpeedToPwm(int nSpeed)
{
	int nPwmValue = 0;
	int nMaxSpeed = 10; //  km/hour
	int nMaxPwm = 100;
	//int a = 0;
	int b = nMaxPwm / nMaxSpeed;

	nPwmValue = b * nSpeed;


	return nPwmValue;
}

void GpioMgr::StartMotorA(int nSpeed)
{
	int nAbsSpeed = abs(nSpeed);
	int nPwmValue = ConvertSpeedToPwm(nAbsSpeed);

	SetMotorA_PWM(nPwmValue);

	if(nSpeed == 0)
	{
		StopMotorA();
	}
	else if(nSpeed > 0)
	{
		SetMotorA_Direction(MotorDir::Forward);
	}
	else if(nSpeed < 0)
	{
		SetMotorA_Direction(MotorDir::Reverse);
	}

}

void GpioMgr::StopMotorA()
{
	digitalWrite (_LogicControl1_MotorA_pin, HIGH) ;

	digitalWrite (_LogicControl2_MotorA_pin, HIGH) ;
}

void GpioMgr::SetMotorA_Direction(MotorDir motorDir)
{
	if(motorDir == MotorDir::Forward)
	{
		digitalWrite (_LogicControl1_MotorA_pin, HIGH) ;

		digitalWrite (_LogicControl2_MotorA_pin, LOW) ;
	}
	else if(motorDir == MotorDir::Reverse)
	{
		digitalWrite (_LogicControl1_MotorA_pin, LOW) ;

		digitalWrite (_LogicControl2_MotorA_pin, HIGH) ;
	}
}

void GpioMgr::SetMotorA_SpeedAsPwmValue(int nPwmValue)
{
	//set direction
	digitalWrite (_LogicControl1_MotorA_pin, HIGH) ;
	digitalWrite (_LogicControl2_MotorA_pin, LOW) ;



	SetMotorA_PWM(nPwmValue);

}

void GpioMgr::SetMotorB_PWM(int nValue)
{
	softPwmWrite (_PWM_MotorB_pin, nValue); /* change the value of PWM */
}
//void ManagePWM();
void GpioMgr::StartMotorB(int nSpeed)
{
	int nAbsSpeed = abs(nSpeed);
	int nPwmValue = ConvertSpeedToPwm(nAbsSpeed);

	SetMotorB_PWM(nPwmValue);

	if(nSpeed == 0)
	{
		StopMotorB();
	}
	else if(nSpeed > 0)
	{
		SetMotorB_Direction(MotorDir::Forward);
	}
	else if(nSpeed < 0)
	{
		SetMotorB_Direction(MotorDir::Reverse);
	}

}

void GpioMgr::StopMotorB()
{
	digitalWrite (_LogicControl1_MotorB_pin, HIGH) ;

	digitalWrite (_LogicControl2_MotorB_pin, HIGH) ;
}

void GpioMgr::SetMotorB_Direction(MotorDir motorDir)
{
	if(motorDir == MotorDir::Forward)
	{
		digitalWrite (_LogicControl1_MotorB_pin, HIGH) ;

		digitalWrite (_LogicControl2_MotorB_pin, LOW) ;
	}
	else if(motorDir == MotorDir::Reverse)
	{
		digitalWrite (_LogicControl1_MotorB_pin, LOW) ;

		digitalWrite (_LogicControl2_MotorB_pin, HIGH) ;
	}
}

void GpioMgr::SetMotorB_Speed(int nSpeed)
{

}





