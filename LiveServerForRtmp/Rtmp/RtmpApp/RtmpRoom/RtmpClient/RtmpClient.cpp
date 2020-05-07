#include "RtmpClient.h"

CRtmpClient::CRtmpClient(int id,  uint32_t chunkSize):m_Chunks(chunkSize)
{

}

CRtmpClient::~CRtmpClient()
{

}

CRtmpClient* CRtmpClient::Create(const int id, const uint32_t chunkSize = 128)
{
	CRtmpClient* pClient = NULL;
	pClient = new CRtmpClient(id,chunkSize);
	return pClient;
}

void CRtmpClient::Destroy()
{
	delete this;
}

int CRtmpClient::Handle(uint8_t *src, const int srcLen)
{
	
}