#pragma once

#include "stdafx.h"

struct CChunkHeader
{
	uint8_t fmt;
	uint32_t csid;
	uint32_t timestamp;
	uint32_t timestampDelta;
	uint32_t messageLength;
	uint8_t messageTypeID;
	uint32_t messageStreamID;
	uint32_t extendedTimestamp;
};

class CChunk
{
public:
	CChunk() = default;
	~CChunk() = default;

	static CChunkHeader* Parse(void* src,const int srcLength,int* outLength);
};
