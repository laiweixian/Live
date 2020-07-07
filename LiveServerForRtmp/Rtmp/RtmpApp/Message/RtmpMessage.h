#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

class CRtmpMessage
{
protected:
	CRtmpMessage();
	~CRtmpMessage();
public:
	static CRtmpMessage* Create(uint8_t msgType,uint8_t *payloadBuf,uint32_t payloadSize);
	void Destroy();
	void SetTimestamp(uint32_t ts);
	void SetStreamId(uint32_t id);
protected:
	uint8_t m_MessageType;
	uint32_t m_PayloadLength;
	uint32_t m_Timestamp;
	uint32_t m_StreamId;

	uint8_t *m_PayloadBuf;
	uint32_t m_PayloadBufSize;
};
