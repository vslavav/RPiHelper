/*
 * UdpClient.h
 *
 *  Created on: 2019-01-27
 *      Author: pi
 */

#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include "GlobalDef.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class UdpClient {
	int _socket;
	struct sockaddr_in     _servaddr;

public:
	UdpClient();
	virtual ~UdpClient();
	void Init();
	void SendMessage(const string sMessage);
};

#endif /* UDPCLIENT_H_ */
