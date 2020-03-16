#include "RtmpMsg.h"

CRtmpMsg::CRtmpMsg(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, uint32_t csid):
							m_Timestamp(ts),m_MessageLength(msgLength),\
							m_MessageTypeID(msgTypeId),m_MessageStreamID(msgStreamId),\
							m_CSID(csid),\
							m_Payload(NULL), m_PayloadLength(0)
{
	m_Payload = new uint8_t[msgLength];
	memset(m_Payload,0,msgLength);
}

CRtmpMsg::~CRtmpMsg()
{
	delete[] m_Payload;
	m_Payload = NULL;
}

uint32_t CRtmpMsg::GetTimestamp()
{
	return m_Timestamp;
}

uint32_t CRtmpMsg::GetMessageLength()
{
	return m_MessageLength;
}

uint8_t CRtmpMsg::GetMessageTypeID()
{
	return m_MessageTypeID;
}

uint32_t CRtmpMsg::GetMessageStreamID()
{
	return m_MessageStreamID;
}

uint32_t CRtmpMsg::GetCSID()
{
	return m_CSID;
}

bool CRtmpMsg::IsEnd()
{
	return (m_MessageLength == m_PayloadLength);
}

int CRtmpMsg::Append(const char* buff, const int buffLen)
{
	const int remainSize = m_MessageLength - m_PayloadLength;
	if (remainSize > buffLen)
		return -1;

	memcpy(m_Payload+ m_PayloadLength,buff,buffLen);
	return 0;
}

uint32_t CRtmpMsg::GetPayloadLength()
{
	return m_PayloadLength;
}

uint8_t* CRtmpMsg::GetPtr()  const 
{
	return m_Payload;
}

uint32_t CRtmpMsg::GetPtrLength() const
{
	return m_PayloadLength;
}