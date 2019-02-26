/*
 * StdIOMgr.cpp
 *
 *  Created on: 2019-01-14
 *      Author: pi
 */

#include <iostream>
#include <thread>
#include "StdIOMgr.h"

using namespace std;



/*void TestStdIn(StdIOMgr* pStdIOMgr)
{
	while(1)
	{
		std::this_thread::sleep_for (chrono::milliseconds(100));

		string sInputLine;

		getline (cin, sInputLine);

		if(sInputLine.empty() == false)
		{

			pStdIOMgr->SetStdInValue(sInputLine);
			sInputLine = "";
		}

	}
}*/



StdIOMgr::StdIOMgr() {
	_IsCommandedExit = false;

}

StdIOMgr::~StdIOMgr() {
	// TODO Auto-generated destructor stub
}

void StdIOMgr::Init()
{
	thread t(&StdIOMgr::TestStdIn, this);


	t.detach();
}

void StdIOMgr::TestStdIn()
{
	while(1)
	{
		std::this_thread::sleep_for (chrono::milliseconds(100));

		string sInputLine;

		getline (cin, sInputLine);

		if(sInputLine.empty() == false)
		{

			SetStdInValue(sInputLine);
			sInputLine = "";
		}

	}
}

void StdIOMgr::Run()
{
	if(_sStdInValue.empty()==false)
	{
		SetStdOutValue(_sStdInValue);//it is echo
		_sStdInValue = "";
	}
}

void StdIOMgr::SetStdInValue(string sValue)
{
	_sStdInValue = sValue;
	if(_sStdInValue.find("exit") != string::npos)
	{
		_IsCommandedExit = true;
	}
}

void StdIOMgr::SetStdOutValue(string sValue)
{
	cout << sValue << endl;
}



