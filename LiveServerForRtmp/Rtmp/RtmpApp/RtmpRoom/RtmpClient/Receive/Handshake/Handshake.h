#pragma once

#include "stdafx.h"

#include "../Receiver.h"

struct HandshakePacket
{
	uint8_t data0[1];
	uint8_t data1[1536];
	uint8_t data2[1536];
};

enum ReceiveHandshakeType{NO_RECEIVE ,C0,C1,C2};
enum SendHandshakeType{NO_SEND,S0,S1,S2};


class CHandshake : public CReciever
{
public:
	CHandshake(IOutStream *pOut);
	~CHandshake();

	int OnReceive(void* src, const int srcLength);

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

	ReceiveHandshakeType m_RecieveStatus;
	SendHandshakeType	 m_SendStatus;
};
