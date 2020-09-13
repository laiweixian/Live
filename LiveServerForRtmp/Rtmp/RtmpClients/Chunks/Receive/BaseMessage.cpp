#include "BaseMessage.h"

CBaseMessage::CBaseMessage()
{
	memset(&m_Header, 0, sizeof(Header));
	memset(&m_Payload, 0, sizeof(Payload));
}

CBaseMessage::CBaseMessage(uint8_t msgType, uint32_t payloadLength, uint32_t timestamp, uint32_t msid, uint8_t* payloadBuf, uint32_t payloadBufLen)
{
	memset(&m_Header, 0, sizeof(Header));
	memset(&m_Payload, 0, sizeof(Payload));

	SetHeader(msgType, payloadLength, timestamp, msid);
	SetPayload(payloadBuf, payloadBufLen);
}

CBaseMessage::~CBaseMessage()
{

}

void CBaseMessage::SetHeader(uint8_t msgType, uint32_t payloadLength, uint32_t timestamp, uint32_t msid)
{
	m_Header.msgType = msgType;
	m_Header.payloadLength = payloadLength;
	m_Header.timestamp = timestamp;
	m_Header.msid = msid;

	m_Payload.bufSize = payloadLength;
	m_Payload.buf = new uint8_t[payloadLength];
	memset(m_Payload.buf, 0, payloadLength);
	m_Payload.ptr = m_Payload.buf;
}

void CBaseMessage::SetPayload(uint8_t* buf, uint32_t bufLength)
{
	if (m_Payload.buf != NULL && m_Payload.bufSize == bufLength)
	{
		memcpy(m_Payload.buf, buf, bufLength);
		m_Payload.ptr += bufLength;
	}
}

void CBaseMessage::AppendPayload(uint8_t* buf, uint32_t bufLength) 
{
	const uint32_t remain = m_Payload.buf + m_Payload.bufSize - m_Payload.ptr;
	if (bufLength > remain)
		return;
	
	memcpy(m_Payload.ptr,buf,bufLength);
	m_Payload.ptr += bufLength;
}

CBaseMessage::Header CBaseMessage::GetHeader()
{
	return m_Header;
}

CBaseMessage::Payload CBaseMessage::GetPayload()
{
	return m_Payload;
}