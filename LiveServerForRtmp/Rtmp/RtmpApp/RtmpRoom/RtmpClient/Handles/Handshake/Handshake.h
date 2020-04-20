#pragma once

#include "../Handle.h"

#define HANDSHAKE_OK			0
#define HANDSHAKE_FAILURE		1
#define ERROR_DATA_LOSS			-1
#define ERROR_VERSION			-2
#define ERROR_TIMESTAMP			-3
#define	ERROR_NO_EVENT			-4
#define ERROR_NO_CALL			-5

#define DECLARE_HANDSHAKE					\
		enum ReceType { NONE, C0, C1, C2 };	\
		enum SendType { NONE, S0, S1, S2 };	\
		struct Packet { uint8_t data0[1];uint8_t data1[1536];uint8_t data2[1536];};


class IHandshakeEvent : public IHandleBaseEvent
{
protected:
	virtual ~IHandshakeEvent() = default;
public:
	IHandshakeEvent() = default;

	virtual void OnC0() = 0;
	virtual void OnC1() = 0;
	virtual void OnC2() = 0;
};

class IHandshakeCall
{
protected:
	IHandshakeCall() = default;
	~IHandshakeCall() = default;
public:
	virtual int SendHandshakePacket(uint8_t *src,const int srcLen) = 0;
};


class CHandshake 
{
public:
	CHandshake(IHandshakeCall *pCall,IHandshakeEvent* pEvent);
	~CHandshake();

	int OnHandshake(uint8_t* src, const int srcLength) ;
private:
	DECLARE_HANDSHAKE
	int ReiceivePacket(char *buff, const int buffLen,int *outLen);
	int ReceiveC0(char *buff, const int buffLen, int *outLen);
	int ReceiveC1(char *buff, const int buffLen, int *outLen);
	int ReceiveC2(char *buff, const int buffLen, int *outLen);

	void SendS0_S1();
	void SendS2();
private:
	IHandshakeCall  *m_pCall;
	IHandshakeEvent *m_pEvent;

	CHandshake::ReceType  m_ReceType;
	CHandshake::SendType  m_SendType;
	CHandshake::Packet    m_RecePack;
	CHandshake::Packet    m_SendPack;
};


