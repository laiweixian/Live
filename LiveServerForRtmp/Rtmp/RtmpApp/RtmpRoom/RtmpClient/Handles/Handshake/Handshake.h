#pragma once

#include "../Handle.h"

#define DATA_LACK (int(-1))
#define RTMP_VERSION_ERR (int(-2))

class IHandshakeEvent;
class CHandshake;

class IHandshakeEvent : public IHandleBaseEvent
{
protected:
	virtual ~IHandshakeEvent() = default;
public:
	IHandshakeEvent() = default;

	virtual bool OnSendHandshake(uint8_t* pData, const int dataLen) = 0;
};

class CHandshake 
{
	enum ReceType { NONE, C0, C1, C2 };
	enum SendType { NONE, S0, S1, S2 };
	struct Packet {uint8_t data0[1];uint8_t data1[1536];uint8_t data2[1536];};

public:
	CHandshake(IHandshakeEvent* pEvent);
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
	IHandshakeEvent *m_Event;

	CHandshake::ReceType  m_ReceType;
	CHandshake::SendType  m_SendType;
	CHandshake::Packet    m_RecePack;
	CHandshake::Packet    m_SendPack;
};


