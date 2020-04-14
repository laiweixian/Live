#pragma once

#include "../Handle.h"
#include "ChunkHeader/ChunkHeader.h"
#include "RtmpMessage/RtmpMessage.h"

class IMessageEvent : public IHandleBaseEvent
{
protected:
	virtual ~IMessageEvent() = default;
public:
	IMessageEvent() = default;

	virtual bool OnSendMessage(uint8_t* pData, const int dataLen) = 0;
};

class CChunks 
{
public:
	CChunks(IMessageEvent* pEvent,const uint32_t chunkSize = 128);
	~CChunks();

	int OnChunk(uint8_t* src, const int srcLength);
private:
	int ParseChunk(uint8_t* src, const int srcLength,int* outHeaderLen,int* outDataLen,CBaseMessage** outMsg);
	CChunkHeader* ParseChunkHeader(uint8_t* src, const int srcLength,int* outLen);
	CBaseMessage* ParseMessage(CChunkHeader* pHeader , uint8_t* src, const int srcLength);


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
	IMessageEvent *m_Event;
	uint32_t m_ChunkSize;

	CChunkHeader *m_NewHeader;
	CBaseMessage *m_NewMsg;
};
