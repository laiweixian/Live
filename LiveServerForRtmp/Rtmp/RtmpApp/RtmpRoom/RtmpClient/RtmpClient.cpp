#include "RtmpClient.h"

CRtmpClient::CRtmpClient(uint32_t chunkSize): m_Handshake(this, this),m_Chunks(this,this,chunkSize)
{

}

