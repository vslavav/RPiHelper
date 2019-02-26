/*
 * Timer.cpp
 *
 *  Created on: 2019-02-04
 *      Author: pi
 */

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub
	_IsRunning = false;
	_timerType = TimerType::Continuous;
}

Timer::Timer(TimerType tt)
{
	_IsRunning = false;
	_timerType = tt;
}

Timer::~Timer() {
	Stop();
}

void Timer::Start()
{
	if(_timerType == TimerType::Continuous)
	{
		Start_Continuous();
	}
	else
	{
		Start_OneShot();
	}


}

void Timer::Start_OneShot()
{
	_thread = thread([&]()
		{
			auto delta = chrono::steady_clock::now() + chrono::milliseconds(_lInterval);
			this_thread::sleep_until(delta);
			_CallBack(this);
			Stop();
		}
	);

	_thread.detach();
}

void Timer::Start_Continuous()
{
	_IsRunning = true;
	_thread = thread([&]() {
				while (_IsRunning)
				{
					auto delta = chrono::steady_clock::now() + chrono::milliseconds(_lInterval);

					this_thread::sleep_until(delta);

					_CallBack(this);
				}
			});

	_thread.detach();
}

void Timer::Stop()
{
	_IsRunning = false;
	_thread.~thread();
}

void Timer::SetInterval(long lInterval)
{
	_lInterval = lInterval;
}

void Timer::SetCallBack(function<void(void*)> func)
{
	_CallBack = func;
}

