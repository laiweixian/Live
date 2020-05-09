#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"






class CRtmpClient  :public CHandshake , public CChunks
{
public:
	static CRtmpClient* Create(const int id, const uint32_t chunkSize = 128);
	void Destroy();
	int Handle(uint8_t *src, const int srcLen);

private:
	CRtmpClient(int id,uint32_t chunkSize);
	~CRtmpClient();

protected:
	//CHandshake
	int SendPacket(const uint8_t* src, const int srcLength);
	int CHandshake::CloseServer() ;

	//
	void OnC0();
	void OnC1();
	void OnC2();

	//
	int SendChunks(uint8_t* src, const int srcLength);
	int CChunks::CloseServer();

	void OnSetChunkSize() ;
	void OnAbortMessage() ;
	void OnAcknowledgement() ;
	void OnWindowAcknowledgementSize() ;
	void OnSetPeerBandwidth();
	void OnUserControlMessages();
	void OnCommandMessage() ;
	void OnDataMessage() ;
	void OnSharedObjectMessage();
	void OnAudioMessage();
	void OnVideoMessage() ;
	void OnAggregateMessage();

private:
	uint64_t m_TotalReceive;


};
