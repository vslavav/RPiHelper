/*
 * UdpSrv.cpp
 *
 *  Created on: 2019-01-29
 *      Author: pi
 */

#include "UdpSrv.h"
#include <thread>
#include <unistd.h>
#include <string.h>


////https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.hala001/xsocudp.htm

void Thread_Run(UdpSrv* pUdpSrv)
{
	while(1)
	{
		//UdpSrv* pUdpSrv = static_cast<UdpSrv*> (pUdpSrv);
		//UdpSrv* pUdpSrv = (UdpSrv*) pUdpSrv;
		pUdpSrv->Run();

	}
}


UdpSrv::UdpSrv() {
	// TODO Auto-generated constructor stub

}

UdpSrv::~UdpSrv() {
	// TODO Auto-generated destructor stub
	close(_socket);
}

void UdpSrv::Init()
{
	unsigned short shPort = 14010;

	_socket = socket(AF_INET, SOCK_DGRAM, 0);

	_server.sin_family      = AF_INET;  /* Server is in Internet Domain */
	_server.sin_port        =  htons(shPort);
	_server.sin_addr.s_addr = INADDR_ANY;/* Server's Internet Address   */

	if (bind(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0)
	{
	   return;
	}

	thread t(Thread_Run,this);
	t.detach();


}

void UdpSrv::Run()
{
	char buff[1024];
	memset(buff,0,1024);
	int client_address_size = sizeof(_client);
	while(1)
	{
		int nError = recvfrom(_socket, buff, sizeof(buff), 0, (struct sockaddr *) &_client,
			            (socklen_t*)&client_address_size) ;
		if(nError < 0)
		{
			perror("recvfrom()");
			return;
		}

		string sMsg = buff;
		memset(buff,0,1024);
		SetMessage( sMsg );

	}
}

void UdpSrv::SetMessage(string sMsg)
{
	_sMessage = sMsg;
}

string UdpSrv::GetMessage()
{
	string sMsg = _sMessage;
	_sMessage = "";

	return sMsg;
}

