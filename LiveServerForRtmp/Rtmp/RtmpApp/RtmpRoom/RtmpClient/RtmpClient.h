#pragma once

#include "Handles/Handles.h"

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
	IRtmpClient(int id, IRtmpClientCall* pCall,IRtmpClientEvent* pEvent);
	~IRtmpClient() = default;
public:
	virtual int GetId() final;
	virtual int OnReceive(uint8_t *src,const int srcLen) = 0;

protected:
	int m_id;
	IRtmpClientCall *m_pCall;
	IRtmpClientEvent *m_pEvent;
};




class CRtmpClient : public IHandshakeEvent , public IHandshakeCall ,	
				    public IMessageEvent , public IMessageCall
{
public:
	CRtmpClient();
	~CRtmpClient();

	//interface
public:
	//IHandshakeEvent
	void OnC0();
	void OnC1();
	void OnC2();
	//IHandshakeCall
	int SendHandshakePacket(uint8_t *src, const int srcLen) = 0;

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

private:
	CHandshake m_Handshake;
	CChunks	   m_Chunks;

	//统计信息

};
