/*
 * ServoSg90Control.h
 *
 *  Created on: 2019-02-12
 *      Author: pi
 */

#ifndef SERVOSG90CONTROL_H_
#define SERVOSG90CONTROL_H_

#include "GlobalDef.h"

class ServoSg90Control {
	int _nServoPwmControl_pin;

	int _nPositionDegree;
	bool _IsStopCommanded;
public:
	ServoSg90Control();
	virtual ~ServoSg90Control();

	void Init();

	void Init_IO();
	void Start();
	void Stop();
	void Run();
	void SetPositionDegree(int nVal){_nPositionDegree = nVal;}
	chrono::microseconds  ConvertPositionDegreeToDuration();
};

#endif /* SERVOSG90CONTROL_H_ */
