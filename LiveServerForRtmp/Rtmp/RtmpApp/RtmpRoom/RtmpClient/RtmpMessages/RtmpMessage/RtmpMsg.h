#pragma once

#include "stdafx.h"

class CRtmpMsg
{
public:
	CRtmpMsg(uint32_t ts,uint32_t msgLength,uint8_t msgTypeId,uint32_t msgStreamId,uint32_t csid);
	~CRtmpMsg();

	uint32_t GetTimestamp();
	uint32_t GetMessageLength();
	uint8_t GetMessageTypeID();
	uint32_t GetMessageStreamID();

	uint32_t GetCSID();

	int Append(const char* buff , const int buffLen);
	uint32_t GetPayloadLength();
	bool IsEnd() ;

	uint8_t* GetPtr() const ;
	uint32_t GetPtrLength() const;
	
private:
	uint32_t m_Timestamp;
	uint32_t m_MessageLength;
	uint8_t  m_MessageTypeID;
	uint32_t m_MessageStreamID;

	uint32_t m_CSID;

	uint8_t *m_Payload;
	uint32_t m_PayloadLength;
};