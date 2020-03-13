#pragma once

#include <stdio.h>
#include <stdint.h>

class CRtmpMessage
{
public:
	CRtmpMessage();
	~CRtmpMessage();
private:
	uint32_t m_Timestamp;
	uint32_t m_Length;
	uint8_t  m_TypeId;
	uint32_t m_MessageStreamID;
};