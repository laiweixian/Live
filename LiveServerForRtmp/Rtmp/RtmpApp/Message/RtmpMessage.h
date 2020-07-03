#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

class CRtmpMessage
{
protected:
	CRtmpMessage(uint8_t msgType,uint32_t payloadLength,uint32_t ts,uint32_t streamId,uint8_t* payloadBuf,uint32_t payloadBufSize);
	~CRtmpMessage();
public:
	static CRtmpMessage* Create(uint8_t msgType, uint32_t payloadLength, uint32_t ts, uint32_t streamId, uint8_t* payloadBuf, uint32_t payloadBufSize);
	void Destroy();

	

protected:
	uint8_t m_MessageType;
	uint32_t m_PayloadLength;
	uint32_t m_Timestamp;
	uint32_t m_StreamId;

	uint8_t *m_PayloadBuf;
	uint32_t m_PayloadBufSize;
};
