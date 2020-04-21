#pragma once

#include "../Handle.h"

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
		enum ReceType { NONE, C0, C1, C2 };	\
		enum SendType { NONE, S0, S1, S2 };	\
		struct Packet { uint8_t data0;uint8_t data1[1536];uint8_t data2[1536];};


class IHandshakeEvent : public IHandleBaseEvent
{
protected:
	virtual ~IHandshakeEvent() = default;
	IHandshakeEvent() = default;
public:
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
	virtual int SendHandshake(uint8_t *src,const int srcLen) = 0;
	virtual int CloseHandshake() = 0;
};


class CHandshake 
{
public:
	CHandshake(IHandshakeCall *pCall,IHandshakeEvent* pEvent);
	~CHandshake();

	int OnHandshake(uint8_t* src, const int srcLength,uint32_t *outLen);
	
private:
	DECLARE_HANDSHAKE
	int ReiceivePacket(uint8_t *buff, const int buffLen,int *outLen);
	int ReceiveC0(uint8_t *buff, const int buffLen, int *outLen);
	int ReceiveC1(uint8_t *buff, const int buffLen, int *outLen);
	int ReceiveC2(uint8_t *buff, const int buffLen, int *outLen);

	int SendPacket();
	int SendS0();
	int SendS1();
	int SendS2();
private:
	IHandshakeCall  *m_pCall;
	IHandshakeEvent *m_pEvent;

	CHandshake::ReceType  m_ReceType;
	CHandshake::SendType  m_SendType;
	CHandshake::Packet    m_RecePack;
	CHandshake::Packet    m_SendPack;
};


