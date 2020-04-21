#include "RtmpClient.h"

CRtmpClient::CRtmpClient(int id, IRtmpClientCall* pCall, IRtmpClientEvent* pEvent, uint32_t chunkSize):\
					IRtmpClient(id,pCall,pEvent),
					m_Handshake(this,this),m_Chunks(this,this, chunkSize)
{

}

CRtmpClient::~CRtmpClient()
{

}

IRtmpClient* CRtmpClient::Create(int id, IRtmpClientCall* pCall, IRtmpClientEvent* pEvent, const uint32_t chunkSize = 128)
{
	CRtmpClient* pClient = NULL;
	pClient = new CRtmpClient(id,pCall,pEvent,chunkSize);
	return pClient;
}

void CRtmpClient::Destroy()
{
	delete this;
}

int CRtmpClient::OnReceive(uint8_t *src, const int srcLen)
{

}

//IHandshakeEvent
void CRtmpClient::OnC0(){}
void CRtmpClient::OnC1(){}
void CRtmpClient::OnC2(){}

//IHandshakeCall
int CRtmpClient::SendHandshake(uint8_t *src, const int srcLen)
{
	return m_pCall->Send(this->GetId(),src,srcLen);
}

int CRtmpClient::CloseHandshake()
{
	return m_pCall->Close(this->GetId());
}

//IMessageEvent
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

void CRtmpClient::OnCommandMessage(CCommandMessage* pMsg)
{

}

void CRtmpClient::OnDataMessage()
{

}

void CRtmpClient::OnSharedObjectMessage()
{

}

void CRtmpClient::OnAudioMessage(CAudioMessage* pMsg)
{

}

void CRtmpClient::OnVideoMessage(CVideoMessage* pMsg)
{

}

void CRtmpClient::OnAggregateMessage()
{

}

//IMessageCall
int CRtmpClient::SendChunk(uint8_t *src, const int srcLen)
{
	return m_pCall->Send(this->GetId(),src,srcLen);
}

int CRtmpClient::CloseChunk()
{
	return m_pCall->Close(this->GetId());
}
