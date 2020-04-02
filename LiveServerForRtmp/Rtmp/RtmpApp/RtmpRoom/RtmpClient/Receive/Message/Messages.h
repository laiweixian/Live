#pragma once


#include "RtmpMessage/RtmpMessage.h"
#include "Chunk/Chunk.h"

class IMessages
{
protected:
	~IMessages() = default;
public:
	IMessages() = default;

	virtual void SetChunkSize(CSetChunkSize* pMsg) = 0;
	virtual void AbortMessage(CAbortMessage* pMsg) = 0;
	virtual void Acknowledgement(CAcknowledgement* pMsg) = 0;
	virtual void WindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg) = 0;
	virtual void SetPeerBandwidth(CSetPeerBandwidth* pMsg) = 0;
	virtual void UserControlMessages(CUserControlMessages* pMsg) = 0;
	virtual void CommandMessage(CCommandMessage* pMsg) = 0;
	virtual void DataMessage(CDataMessage* pMsg) = 0;
	virtual void SharedObjectMessage(CSharedObjectMessage* pMsg) = 0;
	virtual void AudioMessage(CAudioMessage* pMsg) = 0;
	virtual void VideoMessage(CVideoMessage* pMsg) = 0;
	virtual void AggregateMessage(CAggregateMessage* pMsg) = 0;
};

class CMessages : public IMessages
{
public:
	CMessages(const int chunkSize = 128);
	~CMessages();


	int OnRtmpMessage(uint8_t* src, const int srcLength);
private:
	

	int ParseChunk(uint8_t* src, const int srcLength);
	CChunkHeader* ParseChunkHeader(uint8_t* src, const int srcLength,int* outLen);
	CBaseMessage* ParseMessage(CChunkHeader* pHeader , uint8_t* src, const int srcLength);

	//IMessages
	void SetChunkSize() ;
	void AbortMessage();
	void Acknowledgement() ;
	void WindowAcknowledgementSize();
	void SetPeerBandwidth();
	void UserControlMessages() ;
	void CommandMessage() ;
	void DataMessage() ;
	void SharedObjectMessage() ;
	void AudioMessage() ;
	void VideoMessage();
	void AggregateMessage();
private:
	uint32_t m_ChunkSize;

	CChunkHeader *m_ChunkHeader;
	CBaseMessage *m_Message;
};
