#include "RtmpClient.h"

CRtmpClient::CRtmpClient(int id,  uint32_t chunkSize):CChunks(chunkSize),\
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

int CRtmpClient::Handle(uint8_t *src, const int srcLen)
{
	
}

//CHandshake
int CRtmpClient::SendPacket(const uint8_t* src, const int srcLength)
{

}

int CHandshake::CloseServer()
{
	
}

void CRtmpClient::OnC0()
{

}

void CRtmpClient::OnC1()
{

}
void CRtmpClient::OnC2()
{

}

//
int CRtmpClient::SendChunks(uint8_t* src, const int srcLength)
{

}
int CChunks::CloseServer()
{

}

void CRtmpClient::OnSetChunkSize()
{

}
void CRtmpClient::OnAbortMessage()
{

}
void CRtmpClient::OnAcknowledgement()
{

}
void CRtmpClient::OnWindowAcknowledgementSize()
{

}
void CRtmpClient::OnSetPeerBandwidth()
{

}
void CRtmpClient::OnUserControlMessages()
{

}
void CRtmpClient::OnCommandMessage()
{
	
}
void CRtmpClient::OnDataMessage()
{

}
void CRtmpClient::OnSharedObjectMessage()
{

}
void CRtmpClient::OnAudioMessage()
{

}
void CRtmpClient::OnVideoMessage()
{

}
void CRtmpClient::OnAggregateMessage()
{

}