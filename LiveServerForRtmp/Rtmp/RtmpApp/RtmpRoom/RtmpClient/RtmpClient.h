#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Chunks/Chunks.h"


class CRtmpClient  :public CHandshake , public CChunks
{
private:
	CRtmpClient(int id,uint32_t chunkSize);
	~CRtmpClient();

protected:
	//CHandshake
	int SendPacket(const uint8_t* src, const int srcLength);
	int CHandshake::CloseServer() = 0;

	//
	void OnC0();
	void OnC1();
	void OnC2();

	//


public:
	static CRtmpClient* Create(const int id,const uint32_t chunkSize = 128);
	void Destroy();

	int Handle(uint8_t *src, const int srcLen) ;

};
