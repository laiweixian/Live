#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"

class IRtmpClientCall
{
protected:
	IRtmpClientCall() = default;
	~IRtmpClientCall() = default;
public:
	virtual int Send(const int clientid, uint8_t *src, const int srcLen) = 0;
	virtual int Close(const int clientid) = 0;
};

class IRtmpClientEvent
{
protected:
	IRtmpClientEvent() = default;
	~IRtmpClientEvent() = default;
public:
	
};

class IRtmpClient
{
protected:
	IRtmpClient(int id, IRtmpClientCall* pCall, IRtmpClientEvent* pEvent) : \
				m_id(id),m_pCall(pCall),m_pEvent(pEvent){}
	~IRtmpClient() = default;
public:
	virtual void Destroy() = 0;
	virtual int GetId() final{return m_id;}
	virtual int OnReceive(uint8_t *src, const int srcLen) = 0;
protected:
	int					 m_id;
	IRtmpClientCall		*m_pCall;
	IRtmpClientEvent	*m_pEvent;
};


class CRtmpClient : public IRtmpClient,
					public IHandshakeEvent, public IHandshakeCall ,	
				    public IMessageEvent,	public IMessageCall
{
private:
	CRtmpClient(int id, IRtmpClientCall* pCall, IRtmpClientEvent* pEvent,uint32_t chunkSize);
	~CRtmpClient();

public:
	static IRtmpClient* Create(int id, IRtmpClientCall* pCall, IRtmpClientEvent* pEvent,const uint32_t chunkSize = 128);
	void Destroy();
	int OnReceive(uint8_t *src, const int srcLen) ;

private:
	//IHandshakeEvent
	void OnC0();
	void OnC1();
	void OnC2();
	//IHandshakeCall
	int SendHandshake(uint8_t *src, const int srcLen);
	int CloseHandshake();

	//IMessageEvent
	void OnSetChunkSize() ;
	void OnAbortMessage();
	void OnAcknowledgement();
	void OnWindowAcknowledgementSize();
	void OnSetPeerBandwidth();
	void OnUserControlMessages() ;
	void OnCommandMessage(CCommandMessage* pMsg);
	void OnDataMessage() ;
	void OnSharedObjectMessage();
	void OnAudioMessage(CAudioMessage* pMsg) ;
	void OnVideoMessage(CVideoMessage* pMsg);
	void OnAggregateMessage() ;
	
	//IMessageCall
	int SendChunk(uint8_t *src, const int srcLen) ;
	int CloseChunk();

private:
	CHandshake m_Handshake;
	CChunks	   m_Chunks;
};
