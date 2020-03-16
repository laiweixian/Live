#include "RtmpMsg.h"

CRtmpMsg::CRtmpMsg(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId):
							m_Timestamp(ts),m_MessageLength(msgLength),\
							m_MessageTypeID(msgTypeId),m_MessageStreamID(msgStreamId),\
							m_Payload(NULL),m_PayloadLen(0)
{
	m_Payload = new uint8_t[msgLength];
	memset(m_Payload,0,msgLength);
}

CRtmpMsg::~CRtmpMsg()
{

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

int CRtmpMsg::Append(const char* buff, const int buffLen)
{
	const int remainSize = m_MessageLength - m_PayloadLen;
	if (remainSize > buffLen)
		return -1;

	memcpy(m_Payload+m_PayloadLen,buff,buffLen);
	return 0;
}

uint32_t CRtmpMsg::GetPayloadLength()
{
	return m_PayloadLen;
}