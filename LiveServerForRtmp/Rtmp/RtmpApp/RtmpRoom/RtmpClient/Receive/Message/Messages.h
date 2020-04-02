#pragma once


#include "RtmpMessage/RtmpMessage.h"
#include "Chunk/Chunk.h"

class IMessageHandle
{
protected:
	~IMessageHandle() = default;
public:
	IMessageHandle() = default;

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

class CMessages : public IMessageHandle
{
public:
	CMessages(const int chunkSize = 128);
	~CMessages();


	int OnRtmpMessage(uint8_t* src, const int srcLength);
private:
	int ParseChunk(uint8_t* src, const int srcLength,int* outHeaderLen,int* outDataLen,CBaseMessage** outMsg);
	CChunkHeader* ParseChunkHeader(uint8_t* src, const int srcLength,int* outLen);
	CBaseMessage* ParseMessage(CChunkHeader* pHeader , uint8_t* src, const int srcLength);

	//IMessageHandle
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
