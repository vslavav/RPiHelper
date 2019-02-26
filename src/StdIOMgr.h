/*
 * StdIOMgr.h
 *
 *  Created on: 2019-01-14
 *      Author: pi
 */

#ifndef STDIOMGR_H_
#define STDIOMGR_H_

#include "GlobalDef.h"

using namespace std;

class StdIOMgr;

//void TestStdIn(StdIOMgr* pStdIOMgr);


class StdIOMgr {
	string _sStdInValue;
	bool _IsCommandedExit;

public:
	StdIOMgr();
	virtual ~StdIOMgr();

	void Init();
	void Run();
	void TestStdIn();

	void SetStdInValue(string sValue);
	void SetStdOutValue(string sValue);

	bool IsCommandedExit(){return _IsCommandedExit;}
};

#endif /* STDIOMGR_H_ */
