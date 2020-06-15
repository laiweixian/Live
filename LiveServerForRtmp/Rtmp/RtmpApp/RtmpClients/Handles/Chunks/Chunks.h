#pragma once

#include "ReceChunk/ReceChunk.h"
#include "../../Player.h"
#include "../../Publisher.h"

class CChunks :public CPlayer, public CPublisher, public CReceiveChunk
{
protected:
	CChunks(string appName,uint32_t chunkSize);
	virtual ~CChunks();
	
private:
	uint32_t GetChunkSize();

	void HandleSetChunkSize(CSetChunkSize* pMsg) ;
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
	string m_Application;
	uint32_t m_ChunkSize;
};
