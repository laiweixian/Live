#pragma once
#include "stdafx.h"

#define HANDSHAKE_OK			0
#define HANDSHAKE_FAILURE		1

#define RECE_NONE	-1
#define C0			0
#define C1			1
#define C2			2
#define SEND_NONE	RECE_NONE
#define S0			C0
#define	S1			C1
#define S2			C2

#define DECLARE_HANDSHAKE					\
		struct Packet { uint8_t data0[1];uint8_t data1[1536];uint8_t data2[1536];};

class CHandshake 
{
protected:
	CHandshake();
	virtual ~CHandshake();

protected:
	virtual int OnHandshake(uint8_t* src, const int srcLength) final;
	virtual bool HandshakeEnd() final;

protected:
	virtual int Send2Peer( uint8_t* src, const int srcLength) = 0;

private:
	DECLARE_HANDSHAKE
	int RecePacket(uint8_t *buff, const int buffLen,int *outLen);
	int ReceC0(uint8_t *buff, const int buffLen, int *outLen);
	int ReceC1(uint8_t *buff, const int buffLen, int *outLen);
	int ReceC2(uint8_t *buff, const int buffLen, int *outLen);

	int SendPacket();
	int SendS0();
	int SendS1();
	int SendS2();

	int SendHandshake( uint8_t *pSrc, const int srcLen);
private:
	int  m_ReceState;
	int  m_SendState;
	CHandshake::Packet    m_RecePack;
	CHandshake::Packet    m_SendPack;
};


