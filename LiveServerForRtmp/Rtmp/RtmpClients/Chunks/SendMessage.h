#pragma once

#include "RtmpMessage/AbortMessage.h"
#include "RtmpMessage/Acknowledgement.h"
#include "RtmpMessage/AggregateMessage.h"
#include "RtmpMessage/AudioMessage.h"
#include "RtmpMessage/CommandMessage.h"
#include "RtmpMessage/DataMessage.h"
#include "RtmpMessage/SetChunkSize.h"
#include "RtmpMessage/SetPeerBandwidth.h"
#include "RtmpMessage/SharedObjectMessage.h"
#include "RtmpMessage/UserControlMessages.h"
#include "RtmpMessage/VideoMessage.h"
#include "RtmpMessage/WindowAcknowledgementSize.h"

#include "Receive/Chunking.h"

class CSendMessage
{
protected:
	CSendMessage();
	virtual ~CSendMessage();
protected:
	int Send2MySelf(CBaseMessage* pMsg);
protected:
	virtual int Send2Peer(uint8_t* src, const int srcLength) = 0;
private:
	void SendSuccess(CBaseMessage* pMsg);
	void OnSendAcknowledgement(CBaseMessage* pMsg);
	void OnSendAggregateMessage(CBaseMessage* pMsg);
	void OnSendAudioMessage(CBaseMessage* pMsg);
	void OnSendCommandMessage(CBaseMessage* pMsg);
	void OnSendAbortMessage(CBaseMessage* pMsg);
	void OnSendSetChunkSize(CBaseMessage* pMsg);
	void OnSendDataMessage(CBaseMessage* pMsg);
	void OnSendSetPeerBandwidth(CBaseMessage* pMsg);
	void OnSendSharedObjectMessage(CBaseMessage* pMsg);
	void OnSendUserControlMessages(CBaseMessage* pMsg);
	void OnSendVideoMessage(CBaseMessage* pMsg);
	void OnSendWindowAcknowledgementSize(CBaseMessage* pMsg);
	


private:
	uint32_t m_ChunkSize;
	CChunking *m_Prev;
};
