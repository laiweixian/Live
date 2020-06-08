#pragma once

#include "../ChunkHeader/ChunkHeader.h"
#include "../RtmpMessage/RtmpMessage.h"

class CReceiveChunk
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	virtual int OnChunks(uint8_t* src, const int srcLength) final;

private:
	int ReadChunk(uint8_t* src, const int srcLength);
	int ReadChunkHeader(uint8_t* src, const int srcLength,CChunkHeader **ppHeader);
	int ReadChunkBody(CChunkHeader* pHeader, uint8_t* src, const int srcLen,bool *outNewMsg);

	
	void RefreshHeader(CChunkHeader *pHeader);
	void RefreshMessage(CBaseMessage *pMsg);

	void OnMessage(CBaseMessage* pMsg);
protected:
	virtual uint32_t GetChunkSize() = 0;

	virtual void OnSetChunkSize(CSetChunkSize* pMsg) = 0;
	virtual void OnAbortMessage(CAbortMessage* pMsg) = 0;
	virtual void OnAcknowledgement(CAcknowledgement* pMsg) = 0;
	virtual void OnWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg) = 0;
	virtual void OnSetPeerBandwidth(CSetPeerBandwidth* pMsg) = 0;
	virtual void OnUserControlMessages(CUserControlMessages* pMsg) = 0;
	virtual void OnCommandMessage(CCommandMessage* pMsg) = 0;
	virtual void OnDataMessage(CDataMessage* pMsg) = 0;
	virtual void OnSharedObjectMessage(CSharedObjectMessage* pMsg) = 0;
	virtual void OnAudioMessage(CAudioMessage* pMsg) = 0;
	virtual void OnVideoMessage(CVideoMessage* pMsg) = 0;
	virtual void OnAggregateMessage(CAggregateMessage* pMsg) = 0;
private:
	CChunkHeader *m_ChunkHeader;
	CBaseMessage *m_Message;
};
