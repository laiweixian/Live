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
	CChunkHeader *pValue = NULL;
	const uint8_t *start = (uint8_t*)src ,*end = (uint8_t*)src + srcLength  - 1;
	uint8_t *ptr = (uint8_t*)src;

	Head head = {0};

	//Basic Header 
	const uint8_t max6Bits = 0x3f;
	const uint8_t min6Bits = 0x00;
	
	//uint8_t fmt = 0x00;
	uint8_t csidBits  = 0xff;
	int csidLength = 0;

	//Message Header
	uint8_t tsBuf[3] = {0};
	uint8_t tsDeltaBuf[3]= {0};
	uint8_t msgLenBuf[3] = {0};
	uint8_t msgTypeIdBuf[1] = {0};
	uint8_t msgStreamIdBuf[4] = {0};

	//Extended Timestamp 
	const uint32_t maxTimestamp = 0xffffff;
	uint8_t exTsBuf[4] = {0};

	if (src == NULL || srcLength == 0)	
		return NULL;

	//Basic Header
	const uint8_t first = *ptr;
	
	csidBits = ((*ptr) << 2) >> 2 ; 
	head.fmt = ((*ptr)>>6);  
	switch (csidBits)
	{
	case max6Bits:	//3 bytes
		CHECK_OFFSET(start,end,ptr,3)
		head.csid = ((*(ptr + 2)) * 256) + (*(ptr+1)) + 64;
		ptr += 3;
		break;
	case min6Bits:	//2 bytes
		CHECK_OFFSET(start, end, ptr, 2)
		head.csid = *(ptr + 1) + 64;
		ptr += 2;
		break;
	default:		//1 byte	
		CHECK_OFFSET(start, end, ptr, 1)
		head.csid = csidBits;
		ptr += 1;
		break;
	}

	//Message Header
	switch (head.fmt)
	{
	case 0x00:	//3,3,1,4
		CHECK_OFFSET(start,end,ptr,11)
		memcpy(tsBuf,ptr,3);
		memcpy(msgLenBuf,ptr+3,3);
		memcpy(msgTypeIdBuf,ptr+3+3,1);
		memcpy(msgStreamIdBuf,ptr+3+3+1,4);

		head.timestamp = ::BigToHost24(tsBuf);
		head.messageLength = ::BigToHost24(msgLenBuf);
		head.messageTypeID = msgTypeIdBuf[0];
		head.messageStreamID = ::BigToHost32(msgStreamIdBuf);
		ptr += 11;
		break;

	case 0x01:	//3,3,1
		CHECK_OFFSET(start, end, ptr, 7)
		memcpy(&tsDeltaBuf, ptr, 3);
		memcpy(&msgLenBuf, ptr + 3, 3);
		memcpy(&msgStreamIdBuf, ptr + 3 + 3, 1);

		head.timestampDelta = ::BigToHost24(tsDeltaBuf);
		head.messageLength = ::BigToHost24(msgLenBuf);
		head.messageTypeID = msgStreamIdBuf[0];
		ptr +=7;
		break;
	case 0x02:	//3
		CHECK_OFFSET(start, end, ptr, 3)
		head.timestampDelta = ::BigToHost24(tsDeltaBuf);
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
	if (head.timestamp == maxTimestamp || head.timestampDelta == maxTimestamp)
	{
		CHECK_OFFSET(start, end, ptr, 4)
		memcpy(exTsBuf,ptr,4);
		head.extendedTimestamp = ::BigToHost32(exTsBuf);
		ptr += 4;
	}

	pValue = new CChunkHeader;
	memset(pValue,0,sizeof(CChunkHeader));

	pValue->m_Head = head;

	*outLength = ptr - start;
	return pValue;
}


void CChunkHeader::CopyFrom(CChunkHeader* pSrc)
{
	switch (this->m_Head.fmt)
	{
	case 0x00:
		// not omit
		break;
	case 0x01:
		//omit message stream id
		this->m_Head.timestamp = pSrc->m_Head.timestamp + this->m_Head.timestampDelta;
		this->m_Head.messageStreamID = pSrc->m_Head.messageStreamID;
		break;
	case 0x02:
		//omit message length,message type id,message stream id
		this->m_Head.timestamp = pSrc->m_Head.timestamp + this->m_Head.timestampDelta;
		this->m_Head.messageLength = pSrc->m_Head.messageLength;
		this->m_Head.messageTypeID = pSrc->m_Head.messageTypeID;
		this->m_Head.messageStreamID = pSrc->m_Head.messageStreamID;
		break;
	case 0x03:
		//omit timestamp , message length,message type id,message stream id
		this->m_Head.timestamp = pSrc->m_Head.timestamp + pSrc->m_Head.timestampDelta;
		this->m_Head.timestampDelta = pSrc->m_Head.timestampDelta;
		this->m_Head.messageLength = pSrc->m_Head.messageLength;
		this->m_Head.messageTypeID = pSrc->m_Head.messageTypeID;
		this->m_Head.messageStreamID = pSrc->m_Head.messageStreamID;
		break;
	default:
		break;
	}
}

CChunkHeader::Head CChunkHeader::GetHead()
{
	return m_Head;
}