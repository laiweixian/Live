#include "RtmpMessage.h"

CRtmpMessage::CRtmpMessage():m_MessageType(0),m_PayloadLength(0),\
							m_Timestamp(0),m_StreamId(0),\
							m_PayloadBuf(NULL),m_PayloadBufSize(0)
{
	
}

CRtmpMessage::~CRtmpMessage()
{

}

CRtmpMessage* CRtmpMessage::Create(uint8_t msgType, uint8_t *payloadBuf, uint32_t payloadSize)
{
	CRtmpMessage* pMsg = new CRtmpMessage;
	pMsg->m_MessageType = msgType;
	pMsg->m_PayloadLength = payloadSize;
	pMsg->m_PayloadBufSize = payloadSize;
	pMsg->m_PayloadBuf = new uint8_t[payloadSize];
	
	memcpy(pMsg->m_PayloadBuf,payloadBuf,payloadSize);
	return pMsg;
}

void CRtmpMessage::Destroy()
{
	if (m_PayloadBuf) delete[] m_PayloadBuf;
	m_PayloadBuf = NULL;
}

void CRtmpMessage::SetTimestamp(uint32_t ts)
{
	m_Timestamp = ts;
}

void CRtmpMessage::SetStreamId(uint32_t id)
{
	m_StreamId = id;
}