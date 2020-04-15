#include "BaseMessage.h"

CBaseMessage::CBaseMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :
		 m_CSID(csid),m_AppendLength(0)
{
	m_Header.timestamp = ts;
	m_Header.messageLength = msgLength;
	m_Header.messageTypeID = msgTypeId;
	m_Header.messageStreamID = msgStreamId;

	m_Payload.buffLength = msgLength;
	m_Payload.buff = new char[msgLength];
	memset(m_Payload.buff,0,msgLength);
}

CBaseMessage::~CBaseMessage()
{
	delete[] m_Payload.buff;
}

uint32_t CBaseMessage::GetTimestamp() const
{
	return m_Header.timestamp;
}

uint32_t CBaseMessage::GetLength() const
{
	return m_Header.messageLength;
}

uint8_t	 CBaseMessage::GetTypeID() const
{
	return m_Header.messageTypeID;
}

uint32_t CBaseMessage::GetStreamID() const
{
	return m_Header.messageStreamID;
}

uint32_t CBaseMessage::GetRemainSize() const
{
	return (m_Header.messageLength - m_AppendLength);
}

int CBaseMessage::Append(const uint8_t* src, const int srcLen)
{
	const int remainSize = GetRemainSize();

	if (srcLen > remainSize)
		return 0;

	memcpy(m_Payload.buff+m_AppendLength,src,srcLen);
	m_AppendLength += srcLen;
	return srcLen;
}