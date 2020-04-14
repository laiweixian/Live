#include "ChunkHeader.h"

#define CHECK_OFFSET(start,end,ptr,offset) \
	if(ptr+offset > end)	return NULL;

CChunkHeader::CChunkHeader() : m_Head({0})
{

}

CChunkHeader::~CChunkHeader()
{

}

CChunkHeader* CChunkHeader::Parse(uint8_t* src, const int srcLength, int* outLength)
{
	CChunkHeader *pValue = nullptr;
	const uint8_t *start = (uint8_t*)src ,*end = (uint8_t*)src + srcLength  - 1;
	uint8_t *ptr = (uint8_t*)src;

	//Basic Header 
	const uint8_t max6Bits = (0xff << 2) >> 2;
	const uint8_t min6Bits = (0x00 << 2) >> 2;
	uint8_t fmt = 0x00;
	uint8_t csidBits  = 0xff;
	int csidLength = 0x00;
	uint32_t csid = 0x00;

	//Message Header
	uint32_t timestamp = 0x00;
	uint32_t timestampDelta = 0x00;
	uint32_t messageLength = 0x00;
	uint8_t messageTypeID = 0x00;
	uint32_t messageStreamID = 0x00;

	//Extended Timestamp 
	const uint32_t maxTimestamp = 0xffffff;
	uint32_t extendedTimestamp = 0x00;

	if (src == NULL || srcLength == 0)	
		return NULL;

	//Basic Header
	fmt = (*ptr) >> 6;
	csidBits = ((*ptr) << 2) >> 2;
	switch (csidBits)
	{
	case max6Bits:	//3 bytes
		CHECK_OFFSET(start,end,ptr,3)
		csid = ((*(ptr + 2)) * 256) + (*(ptr+1)) + 64;
		ptr += 3;
		break;
	case min6Bits:	//2 bytes
		CHECK_OFFSET(start, end, ptr, 2)
		csid = *(ptr + 1) + 64;
		ptr += 2;
		break;
	default:		//1 byte	
		CHECK_OFFSET(start, end, ptr, 1)
		csid  = csidBits;
		ptr += 1;
		break;
	}

	//Message Header
	switch (fmt)
	{
	case 0x00:	//3,3,1,4
		CHECK_OFFSET(start,end,ptr,11)
		memcpy(&timestamp,ptr,3);
		memcpy(&messageLength,ptr+3,3);
		memcpy(&messageTypeID,ptr+3+3,1);
		memcpy(&messageStreamID,ptr+3+3+1,4);

		timestamp = ::BigToHost24(&timestamp);
		messageLength = ::BigToHost24(&messageLength);
		messageTypeID = messageTypeID;
		messageStreamID = ::BigToHost32(&messageStreamID);
		ptr += 11;
		break;

	case 0x01:	//3,3,1
		CHECK_OFFSET(start, end, ptr, 7)
		memcpy(&timestampDelta, ptr, 3);
		memcpy(&messageLength, ptr + 3, 3);
		memcpy(&messageTypeID, ptr + 3 + 3, 1);

		timestampDelta = ::BigToHost24(&timestampDelta);
		messageLength = ::BigToHost24(&messageLength);
		messageTypeID = messageTypeID;
		ptr +=7;
		break;
	case 0x02:	//3
		CHECK_OFFSET(start, end, ptr, 3)
		timestampDelta = ::BigToHost24(&timestampDelta);
		ptr += 3;
		break;
	case 0x03:
		CHECK_OFFSET(start, end, ptr, 0)
		ptr += 0;
		break;
	default:
		break;
	}
	
	//Extended Timestamp 
	if (timestamp == maxTimestamp || timestampDelta == maxTimestamp)
	{
		CHECK_OFFSET(start, end, ptr, 4)
		memcpy(&extendedTimestamp,ptr,4);
		extendedTimestamp = ::BigToHost32(&extendedTimestamp);
		ptr += 4;
	}

	pValue = new CChunkHeader;
	memset(pValue,0,sizeof(CChunkHeader));

	pValue->m_Head.fmt = fmt;
	pValue->m_Head.csid = csid;
	pValue->m_Head.timestamp = timestamp;
	pValue->m_Head.timestampDelta = timestampDelta;
	pValue->m_Head.messageLength = messageLength;
	pValue->m_Head.messageTypeID = messageTypeID;
	pValue->m_Head.messageStreamID = messageStreamID;
	pValue->m_Head.extendedTimestamp = extendedTimestamp;

	*outLength = ptr - start;
	return pValue;
}

CChunkHeader* CChunkHeader::Parse(CChunkHeader::Head header)
{
	CChunkHeader* pValue = new CChunkHeader;

	pValue->m_Head = header;
	return pValue;
}

CChunkHeader::Head CChunkHeader::GetHead()
{
	return m_Head;
}