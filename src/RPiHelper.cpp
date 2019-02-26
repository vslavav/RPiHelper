//============================================================================
// Name        : RPiHelper.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
using namespace std;

#include "TopMgr.h"



int main()
{
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!



	TopMgr* pTopMgr = new TopMgr();
	pTopMgr->Init();
	pTopMgr->Run();

	return 0;
}
