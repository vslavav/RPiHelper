/*
 * UdpClient.cpp
 *
 *  Created on: 2019-01-27
 *      Author: pi
 */

#include "UdpClient.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.hala001/cskudp.htm

UdpClient::UdpClient() {
	// TODO Auto-generated constructor stub


}

UdpClient::~UdpClient() {
	// TODO Auto-generated destructor stub
	close(_socket);
}

void UdpClient::Init()
{
	int nPort = 14000;
	string sIp = "192.168.2.49";
	_socket = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&_servaddr, 0, sizeof(_servaddr));
	// Filling server information
	_servaddr.sin_family = AF_INET;
	_servaddr.sin_port = htons(nPort);
	_servaddr.sin_addr.s_addr = inet_addr(sIp.c_str());

}

void UdpClient::SendMessage(const string sMessage)
{
	sendto(_socket, sMessage.c_str(), sMessage.length(),
	        0, (const struct sockaddr *) &_servaddr,
	            sizeof(_servaddr));
}

