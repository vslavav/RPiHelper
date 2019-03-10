/*
 * GpioMgr.h
 *
 *  Created on: 2019-01-19
 *      Author: pi
 */

#ifndef GPIOMGR_H_
#define GPIOMGR_H_

#include "GlobalDef.h"
#include "Timer.h"

class GpioMgr;
void ManageIO(GpioMgr* pGpioMgr);

enum class MotorDir
{
	Forward,
	Reverse
};



void TimerFunc(void* p);

class USonicSensor;
class ServoSg90Control;
class IrReceiver;
class IrReceiverLIRC;
class OneWireTempSensor;

class GpioMgr {
	condition_variable _cond_var;
	mutex _mutex4cond_var;

	int  _PWM_MotorA_pin;          //EN1

	int  _LogicControl1_MotorA_pin;
	int  _LogicControl2_MotorA_pin;

	int  _PWM_MotorB_pin;          //EN2
	int  _PWM_MotorB_value;

	int  _LogicControl1_MotorB_pin;
	int  _LogicControl2_MotorB_pin;


	Timer _timer1;
	USonicSensor* _pUSonicSensor;
	ServoSg90Control* _pServoSg90Control;
	IrReceiver*       _pIrReceiver;
	IrReceiverLIRC*   _pIrReceiverLIRC;
	OneWireTempSensor* _pOneWireTempSensor;


public:
	GpioMgr();
	virtual ~GpioMgr();
	void Init();
	void InitPins();
	void Init_PWM();


	void SetMotorA_PWM(int nValue);
	//void ManagePWM();
	void StartMotorA(int nSpeed);
	void StopMotorA();
	void SetMotorA_Direction(MotorDir motorDir);
	void SetMotorA_SpeedAsPwmValue(int nPwmValue);

	void SetMotorB_PWM(int nValue);
	//void ManagePWM();
	void StartMotorB(int nSpeed);
	void StopMotorB();
	void SetMotorB_Direction(MotorDir motorDir);
	void SetMotorB_Speed(int nSpeed);


	int ConvertSpeedToPwm(int nSpeed);




	void TimerHelper();
};

#endif /* GPIOMGR_H_ */
