 #pragma once


#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

class IChunkHandle
{
protected:
	IChunkHandle() = default;
	virtual ~IChunkHandle() = default;

	virtual void HandleSetChunkSize(CBaseMessage* pMsg) = 0;
	virtual void HandleAbortMessage(CBaseMessage* pMsg) = 0;
	virtual void HandleAcknowledgement(CBaseMessage* pMsg) = 0;
	virtual void HandleWindowAcknowledgementSize(CBaseMessage* pMsg) = 0;
	virtual void HandleSetPeerBandwidth(CBaseMessage* pMsg) = 0;
	virtual void HandleUserControlMessages(CBaseMessage* pMsg) = 0;
	virtual void HandleCommandMessage(CBaseMessage* pMsg,const bool isVersion3 = false) = 0;
	virtual void HandleDataMessage(CBaseMessage* pMsg, const bool isVersion3 = false) = 0;
	virtual void HandleSharedObjectMessage(CBaseMessage* pMsg, const bool isVersion3 = false) = 0;
	virtual void HandleAudioMessage(CBaseMessage* pMsg) = 0;
	virtual void HandleVideoMessage(CBaseMessage* pMsg) = 0;
	virtual void HandleAggregateMessage(CBaseMessage* pMsg) = 0;
};

class CReceiveChunk : public IChunkHandle
{
protected:
	CReceiveChunk() ;
	virtual ~CReceiveChunk();

protected:
	virtual int OnChunks(uint8_t* src, const int srcLength) final;
private:
	int ReceiveMessage(uint8_t* src,const int srcLen);
	void CReceiveChunk::HandleMessage(CBaseMessage* pMsg);
	virtual void HandleAbortMessage(CBaseMessage* pMsg) final;
protected:
	virtual uint32_t GetChunkSize() = 0;
private:
	CBaseMessage *m_Lastest;
};
