/*
 * TopMgr.h
 *
 *  Created on: 2019-01-14
 *      Author: pi
 */

#ifndef TOPMGR_H_
#define TOPMGR_H_

#include "GlobalDef.h"

class StdIOMgr;
class GpioMgr;
class UdpClient;
class UdpSrv;


class TopMgr {
	StdIOMgr* 	_pStdIOMgr;
	GpioMgr*  	_pGpioMgr;
	UdpClient* 	_pUdpClient;
	UdpSrv*  	_pUdpSrv;
public:
	static TopMgr* _pTopMgr;

public:
	TopMgr();
	virtual ~TopMgr();
	void Init();
	void Run();
	UdpClient* GetUdpClient(){return _pUdpClient;}
protected:
	void ProceeedCmdFromStdIo(string sCmd);
	void ProceeedCmdFromUdp(string sCmd);

};

#endif /* TOPMGR_H_ */
