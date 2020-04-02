#pragma once

#include "stdafx.h"


#define DATA_LACK (int(-1))
#define RTMP_VERSION_ERR (int(-2))

struct HandshakePacket
{
	uint8_t data0[1];
	uint8_t data1[1536];
	uint8_t data2[1536];
};

enum HandshakeReceiveType{INVALID ,C0,C1,C2};
enum HandshakeSendType{INVALID,S0,S1,S2};

class IHandshakeRespose
{
protected:
	IHandshakeRespose() = default;
public:
	IHandshakeRespose() = default;

	virtual void S0(uint8_t* buff, const int buffLen) = 0;
	virtual void S1(uint8_t* buff, const int buffLen) = 0;
	virtual void S2(uint8_t* buff, const int buffLen) = 0;
};

class CHandshake 
{
public:
	CHandshake(IHandshakeRespose *pRespose);
	~CHandshake();

	int OnHandshake(uint8_t* src, const int srcLength) ;
private:
	int ReiceivePacket(char *buff, const int buffLen,int *outLen);
	int ReceiveC0(char *buff, const int buffLen, int *outLen);
	int ReceiveC1(char *buff, const int buffLen, int *outLen);
	int ReceiveC2(char *buff, const int buffLen, int *outLen);

	void SendS0_S1();
	void SendS2();

private:
	IHandshakeRespose* m_Respose;

	HandshakeReceiveType m_RecieveType;
	HandshakeSendType	 m_SendType;
	HandshakePacket m_ReceivePacket;
	HandshakePacket m_SendPacket;
};
