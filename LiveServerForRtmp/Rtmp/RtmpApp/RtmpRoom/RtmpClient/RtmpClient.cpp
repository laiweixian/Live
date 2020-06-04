#include "RtmpClient.h"

CRtmpClient::CRtmpClient(int id,uint32_t chunkSize):CChunks(chunkSize),\
														m_TotalReceive(0)
{

}

CRtmpClient::~CRtmpClient()
{

}

CRtmpClient* CRtmpClient::Create(const int id, const uint32_t chunkSize)
{
	CRtmpClient* pClient = NULL;
	pClient = new CRtmpClient(id,chunkSize);
	return pClient;
}

void CRtmpClient::Destroy()
{
	delete this;
}



//CHandshake
int CRtmpClient::SendPacket(const uint8_t* src, const int srcLength)
{
	return 0;
}

//
int CRtmpClient::SendChunks(uint8_t* src, const int srcLength)
{
	return 0;
}


