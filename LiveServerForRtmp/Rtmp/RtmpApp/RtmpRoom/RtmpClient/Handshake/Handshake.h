#pragma once

#include "stdafx.h"

extern int SendToPeer(char* buff,const int buffLen);

struct HandshakePacket
{
	uint8_t data0[1];
	uint8_t data1[1536];
	uint8_t data2[1536];
};

enum ReceiveHandshake{NO_RECEIVE ,C0,C1,C2};
enum SendHandshake{NO_SEND,S0,S1,S2};


class CHandshake
{
public:
	CHandshake();
	~CHandshake();

	int OnReceive(char *buff,const int buffLen);

private:
	int ReiceivePacket(char *buff, const int buffLen,int *outLen);
	int ReceiveC0(char *buff, const int buffLen, int *outLen);
	int ReceiveC1(char *buff, const int buffLen, int *outLen);
	int ReceiveC2(char *buff, const int buffLen, int *outLen);

	int SendPakcet(int *outLen);
	int SendS0(int *outLen);
	int SendS1(int *outLen);
	int SendS2(int *outLen);

private:
	HandshakePacket m_Receive;
	HandshakePacket m_Send;

	ReceiveHandshake m_RecieveStatus;
	SendHandshake	 m_SendStatus;
};
