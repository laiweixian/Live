#pragma once

#include "stdafx.h"

#include "../DataHandle.h"

#define DATA_LACK (int(-1))
#define RTMP_VERSION_ERR (int(-2))

struct HandshakePacket
{
	uint8_t data0[1];
	uint8_t data1[1536];
	uint8_t data2[1536];
};

enum ReceiveHandshakeType{NO_RECEIVE ,C0,C1,C2};
enum SendHandshakeType{NO_SEND,S0,S1,S2};


class CHandshake : public CDataHandle
{
public:
	CHandshake();
	~CHandshake();

	//CDataHandle
	int OnRequest(uint8_t* src, const int srcLength) ;
	DataHandleType GetType() ;
	void* GetResponse(int* outLen) const ;

private:
	int ReiceivePacket(char *buff, const int buffLen,int *outLen);
	int ReceiveC0(char *buff, const int buffLen, int *outLen);
	int ReceiveC1(char *buff, const int buffLen, int *outLen);
	int ReceiveC2(char *buff, const int buffLen, int *outLen);

	int InitS0();
	int InitS1();
	int InitS2();

private:
	HandshakePacket m_Receive;
	HandshakePacket m_Send;

	ReceiveHandshakeType m_RecieveStatus;
	SendHandshakeType	 m_SendStatus;
};
