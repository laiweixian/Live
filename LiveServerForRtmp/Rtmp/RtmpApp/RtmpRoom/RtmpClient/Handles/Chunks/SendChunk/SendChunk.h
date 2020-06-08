#pragma once

#include "stdafx.h"
#include "../ChunkHeader/ChunkHeader.h"
#include "../RtmpMessage/RtmpMessage.h"

class CSendChunk
{
protected:
	CSendChunk();
	virtual ~CSendChunk();

protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(const uint8_t* src, const int srcLength) = 0;

	int SendMessage(CBaseMessage* pMsg);
private:
	int SendSetChunkSize(CSetChunkSize* pMsg) ;
	int SendAbortMessage(CAbortMessage* pMsg) ;
	int SendAcknowledgement(CAcknowledgement* pMsg) ;
	int SendWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg) ;
	int SendSetPeerBandwidth(CSetPeerBandwidth* pMsg) ;
	int SendUserCSendtrolMessages(CUserControlMessages* pMsg);
	int SendCommandMessage(CCommandMessage* pMsg) ;
	int SendDataMessage(CDataMessage* pMsg) ;
	int SendSharedObjectMessage(CSharedObjectMessage* pMsg) ;
	int SendAudioMessage(CAudioMessage* pMsg);
	int SendVideoMessage(CVideoMessage* pMsg) ;
	int SendAggregateMessage(CAggregateMessage* pMsg) ;
};
