#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"

#include "Player.h"
#include "Publisher.h"


class CRtmpClient : public CPlayer,public CPublish,
					public CHandshake,\
					public CChunks
{
public:
	static CRtmpClient* Create(const int id, const uint32_t chunkSize = 128);
	void Destroy();
	

private:
	CRtmpClient(int id,uint32_t chunkSize);
	~CRtmpClient();

protected:
	//
	int CloseServer();

	//CHandshake
	int SendPacket(const uint8_t* src, const int srcLength);
	
	//CPublisher
	int SendChunks(uint8_t* src, const int srcLength);

	//
public:
	

private:
	uint64_t m_TotalReceive;
};
