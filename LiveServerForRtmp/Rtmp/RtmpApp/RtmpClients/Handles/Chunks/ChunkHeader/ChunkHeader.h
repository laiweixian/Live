#pragma once

#include "stdafx.h"

class CChunkHeader
{
public:
	struct Head {
		uint8_t fmt;
		uint32_t csid;
		uint32_t timestamp;
		uint32_t timestampDelta;
		uint32_t messageLength;
		uint8_t messageTypeID;
		uint32_t messageStreamID;
		uint32_t extendedTimestamp;
	};

private:
	CChunkHeader();
public:
	~CChunkHeader() ;

	static CChunkHeader* Parse(uint8_t* src,const int srcLength,int* outLength);
	void CopyFrom(CChunkHeader* pSrc);

	CChunkHeader::Head GetHead();
protected:
	CChunkHeader::Head m_Head;
};


