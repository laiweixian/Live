 #pragma once

#include "../ChunkHeader/ChunkHeader.h"
#include "Rtmp/RtmpApp/RtmpMessage/RtmpMessage.h"

class IChunkHandle
{
protected:
	IChunkHandle() = default;
	virtual ~IChunkHandle() = default;

	virtual void HandleSetChunkSize(CSetChunkSize* pMsg) = 0;
	virtual void HandleAbortMessage(CAbortMessage* pMsg) = 0;
	virtual void HandleAcknowledgement(CAcknowledgement* pMsg) = 0;
	virtual void HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg) = 0;
	virtual void HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg) = 0;
	virtual void HandleUserControlMessages(CUserControlMessages* pMsg) = 0;
	virtual void HandleCommandMessage(CCommandMessage* pMsg) = 0;
	virtual void HandleDataMessage(CDataMessage* pMsg) = 0;
	virtual void HandleSharedObjectMessage(CSharedObjectMessage* pMsg) = 0;
	virtual void HandleAudioMessage(CAudioMessage* pMsg) = 0;
	virtual void HandleVideoMessage(CVideoMessage* pMsg) = 0;
	virtual void HandleAggregateMessage(CAggregateMessage* pMsg) = 0;
};

class CReceiveChunk : public IChunkHandle
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	virtual int OnChunks(uint8_t* src, const int srcLength) final;
	virtual void HandleAbortMessage(CAbortMessage* pMsg) final;
private:
	int ReadChunk(uint8_t* src, const int srcLength);
	int ReadChunkHeader(uint8_t* src, const int srcLength,CChunkHeader **ppHeader);
	int ReadChunkBody(CChunkHeader* pHeader, uint8_t* src, const int srcLen,bool *outNewMsg);
	
	void RefreshHeader(CChunkHeader *pHeader);
	void RefreshMessage(CBaseMessage *pMsg);

	void HandleMessage(CBaseMessage* pMsg);
protected:
	virtual uint32_t GetChunkSize() = 0;
private:
	CChunkHeader *m_ChunkHeader;
	CBaseMessage *m_Message;
};
