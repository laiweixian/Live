#pragma once
#include "stdafx.h"

#define HANDSHAKE_OK			0
#define HANDSHAKE_FAILURE		1
#define ERROR_HANDSHAKE_END		-1
#define ERROR_DATA_LOSS			-2
#define ERROR_VERSION			-3
#define ERROR_TIMESTAMP			-4
#define	ERROR_NO_EVENT			-5
#define ERROR_NO_CALL			-6
#define	ERROR_SEND_HANDSHAKE	-7

#define DECLARE_HANDSHAKE					\
		enum ReceType { RECE_NONE, C0, C1, C2 };	\
		enum SendType { SEND_NONE, S0, S1, S2 };	\
		struct Packet { uint8_t data0;uint8_t data1[1536];uint8_t data2[1536];};

class CHandshake 
{
protected:
	CHandshake();
	virtual ~CHandshake();

public:
	virtual int OnHandshake(uint8_t* src, const int srcLength,uint32_t *outLen) final;

protected:
	virtual int Send2Peer(const uint8_t* src, const int srcLength) = 0;

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

	int SendHandshake(const uint8_t *pSrc, const int srcLen);
private:
	CHandshake::ReceType  m_ReceType;
	CHandshake::SendType  m_SendType;
	CHandshake::Packet    m_RecePack;
	CHandshake::Packet    m_SendPack;
};


