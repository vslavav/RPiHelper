/*
 * USonicSensor.h
 *
 *  Created on: 2019-02-11
 *      Author: pi
 */

#ifndef USONICSENSOR_H_
#define USONICSENSOR_H_

#include "GlobalDef.h"

class USonicSensor {
	int _nTrigger_pin;
	int _nEcho_pin;
	double _distance;
	bool _IsStopCommanded;
	bool _IsMeasuringDone;
	vector<double> _listValues;
public:
	USonicSensor();
	virtual ~USonicSensor();

	void Init();

	void Init_IO();
	void Start();
	void Stop();
	void Run();
	void Start_MeasureDistance();
	void Stop_MeasureDistance();
	void ProcessValues();
	void MeasureDistance();
	double GetDistance();
	bool IsMeasuringDone(){return _IsMeasuringDone;}
};

#endif /* USONICSENSOR_H_ */
