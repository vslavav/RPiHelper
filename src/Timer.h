/*
 * Timer.h
 *
 *  Created on: 2019-02-04
 *      Author: pi
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "GlobalDef.h"

enum class TimerType
{
	OneShot,
	Continuous
};

class Timer {
	function<void(void*)> _CallBack;
	long _lInterval;
	bool _IsRunning;
	thread _thread;
	TimerType _timerType;
public:
	Timer();
	Timer(TimerType tt);
	virtual ~Timer();
	void Start();
	void Start_OneShot();
	void Start_Continuous();
	void Stop();
	void SetInterval(long lInterval);
	void SetCallBack(function<void(void*)> func);
	void SetTimerType(TimerType tt){_timerType = tt;}

};

#endif /* TIMER_H_ */
