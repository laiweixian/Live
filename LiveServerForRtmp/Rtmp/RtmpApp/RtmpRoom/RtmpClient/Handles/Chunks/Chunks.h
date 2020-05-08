#pragma once

#include "ChunkHeader/ChunkHeader.h"
#include "RtmpMessage/RtmpMessage.h"

class CChunks
{
public:
	CChunks(const uint32_t chunkSize = 128);
	~CChunks();

	virtual int OnChunks(uint8_t* src, const int srcLength) final;

	//call 
	virtual int SendChunks(uint8_t* src, const int srcLength) = 0;
	virtual int CloseServer() = 0;

	//notification
	virtual void OnSetChunkSize() = 0;
	virtual void OnAbortMessage() = 0;
	virtual void OnAcknowledgement() = 0;
	virtual void OnWindowAcknowledgementSize() = 0;
	virtual void OnSetPeerBandwidth() = 0;
	virtual void OnUserControlMessages() = 0;
	virtual void OnCommandMessage() = 0;
	virtual void OnDataMessage() = 0;
	virtual void OnSharedObjectMessage() = 0;
	virtual void OnAudioMessage() = 0;
	virtual void OnVideoMessage() = 0;
	virtual void OnAggregateMessage() = 0;
	
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
