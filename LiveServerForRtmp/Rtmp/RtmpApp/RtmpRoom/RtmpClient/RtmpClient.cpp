#include "RtmpClient.h"

CRtmpClient::CRtmpClient(int id,uint32_t chunkSize):CChunks(chunkSize)
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


int CRtmpClient::Send2Peer(const uint8_t* src, const int srcLength)
{
	return 0;
}
