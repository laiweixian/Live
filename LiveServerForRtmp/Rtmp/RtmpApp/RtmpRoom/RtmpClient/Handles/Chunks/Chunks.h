#pragma once

#include "../Handle.h"
#include "ChunkHeader/ChunkHeader.h"
#include "RtmpMessage/RtmpMessage.h"

class CChunks;
class IMessageEvent;

class IMessageEvent : public IHandleBaseEvent
{
protected:
	virtual ~IMessageEvent() = default;
	IMessageEvent() = default;
public:
	virtual void OnSetChunkSize() = 0;
	virtual void OnAbortMessage() = 0;
	virtual void OnAcknowledgement() = 0;
	virtual void OnWindowAcknowledgementSize() = 0;
	virtual void OnSetPeerBandwidth() = 0;
	virtual void OnUserControlMessages() = 0;
	virtual void OnCommandMessage(CCommandMessage* pMsg) = 0;
	virtual void OnDataMessage() = 0;
	virtual void OnSharedObjectMessage() = 0;
	virtual void OnAudioMessage(CAudioMessage* pMsg) = 0;
	virtual void OnVideoMessage(CVideoMessage* pMsg) = 0;
	virtual void OnAggregateMessage() = 0;
};

class IMessageCall
{
protected:
	IMessageCall() = default; 
	~IMessageCall() = default;
private:
	virtual int SendChunk(uint8_t *src,const int srcLen) = 0;
};

class CChunks 
{
public:
	CChunks(IMessageCall* pCall,IMessageEvent* pEvent,const uint32_t chunkSize = 128);
	~CChunks();

	int OnChunks(uint8_t* src, const int srcLength);
private:
	int OnChunk(uint8_t* src, const int srcLength);
	CChunkHeader* OnChunkHeader(uint8_t* src, const int srcLength, int* outHeadLen);
	CBaseMessage* OnMessage(CChunkHeader* pHeader);
	int OnChunkData( CBaseMessage *pMsg, const int srcLength);

	void HandleMessage(CBaseMessage* pMsg);
	void HandleSetChunkSize(CSetChunkSize* pMsg);
	void HandleAbortMessage(CAbortMessage* pMsg);
	void HandleAcknowledgement(CAcknowledgement* pMsg);
	void HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg);
	void HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg);
	void HandleUserControlMessages(CUserControlMessages* pMsg);
	void HandleCommandMessage(CCommandMessage* pMsg);
	void HandleDataMessage(CDataMessage* pMsg);
	void HandleSharedObjectMessage(CSharedObjectMessage* pMsg);
	void HandleAudioMessage(CAudioMessage* pMsg);
	void HandleVideoMessage(CVideoMessage* pMsg);
	void HandleAggregateMessage(CAggregateMessage* pMsg);

private:
	IMessageCall *m_pCall;
	IMessageEvent *m_pEvent;
	uint32_t m_ChunkSize;

	CChunkHeader *m_NewHeader;
	CBaseMessage *m_NewMsg;
};
