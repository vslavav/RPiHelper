/*
 * UdpSrv.h
 *
 *  Created on: 2019-01-29
 *      Author: pi
 */

#ifndef UDPSRV_H_
#define UDPSRV_H_

#include "GlobalDef.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class UdpSrv;
void Thread_Run(UdpSrv* pUdpSrv);

class UdpSrv {
	int _socket;
	struct sockaddr_in _client;
	struct sockaddr_in _server;
	string _sMessage;
private:
	void SetMessage(string sMsg);

public:
	UdpSrv();
	virtual ~UdpSrv();
	void Init();
	void Run();
	string GetMessage();

};

#endif /* UDPSRV_H_ */
