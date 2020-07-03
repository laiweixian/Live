#include "RtmpMessage.h"

CRtmpMessage::CRtmpMessage(uint8_t msgType, uint32_t payloadLength, uint32_t ts, uint32_t streamId, uint8_t* payloadBuf, uint32_t payloadBufSize):\
	m_MessageType(msgType),m_PayloadLength(payloadLength),\
	m_Timestamp(ts),m_StreamId(streamId)
{
	m_PayloadBufSize = payloadBufSize;
	m_PayloadBuf = new uint8_t[m_PayloadBufSize];
	memcpy(m_PayloadBuf,payloadBuf,m_PayloadBufSize);
}

CRtmpMessage::~CRtmpMessage()
{

}

CRtmpMessage* CRtmpMessage::Create(uint8_t msgType, uint32_t payloadLength, uint32_t ts, uint32_t streamId, uint8_t* payloadBuf, uint32_t payloadBufSize)
{
	if (payloadLength != payloadBufSize)
		return NULL;
	return new CRtmpMessage(msgType,payloadLength,ts,streamId,payloadBuf,payloadBufSize);
}

void CRtmpMessage::Destroy()
{
	if (m_PayloadBuf) delete[] m_PayloadBuf;
	m_PayloadBuf = NULL;
}
