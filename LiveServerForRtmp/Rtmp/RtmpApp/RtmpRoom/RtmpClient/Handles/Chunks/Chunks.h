#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "RtmpMessage/RtmpMessage.h"

class CChunks
{
public:
	CChunks(const uint32_t chunkSize = 128);
	~CChunks();

	int OnChunks(uint8_t* src, const int srcLength);
private:
	int ReceChunk(uint8_t* src, const int srcLength);
	CChunkHeader* ReceChunkHeader(uint8_t* src, const int srcLength, int* outHeadLen);
	bool ReceChunkData(CChunkHeader* pHeader, uint8_t* src, const int srcLen,int* outDataLen);

	void PushMessage(CBaseMessage *pMsg);
	void PushChunkHeader(CChunkHeader *pHeader);

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
	uint32_t m_ChunkSize;
	CChunkHeader *m_ChunkHeader;
	CBaseMessage *m_Message;
};
