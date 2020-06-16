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
protected:
	void HandleSetChunkSize(CBaseMessage* pMsg) ;
	void HandleAcknowledgement(CBaseMessage* pMsg) ;
	void HandleWindowAcknowledgementSize(CBaseMessage* pMsg);
	void HandleSetPeerBandwidth(CBaseMessage* pMsg);
	void HandleUserControlMessages(CBaseMessage* pMsg) ;
	void HandleCommandMessage(CBaseMessage* pMsg, const bool isVersion3 = false);
	void HandleDataMessage(CBaseMessage* pMsg, const bool isVersion3 = false);
	void HandleSharedObjectMessage(CBaseMessage* pMsg, const bool isVersion3 = false) ;
	void HandleAudioMessage(CBaseMessage* pMsg);
	void HandleVideoMessage(CBaseMessage* pMsg) ;
	void HandleAggregateMessage(CBaseMessage* pMsg);

private:
	string m_Application;
	uint32_t m_ChunkSize;
};
