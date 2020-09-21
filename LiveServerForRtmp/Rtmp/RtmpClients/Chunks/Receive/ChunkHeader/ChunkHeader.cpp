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
	
	csidBits = ((first << 2) >> 2) ;
	head.fmt = (first >> 6);
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

uint8_t* CChunkHeader::Encode(Head head, uint32_t* outLength)
{
	uint8_t* buf = NULL,*ptr = NULL ;
	char *tempPtr = NULL;
	uint32_t bufLength = 0;

	//csid
	uint8_t *bufs[3] = { 0 };
	uint32_t bufsLen[3] = { 0 };

	//
	uint32_t bigNumber32 = 0;
	uint32_t bigNumber24 = 0;
	uint16_t bigNumber16 = 0;

	//
	int i = 0;


	//±àÂëCSID
	if (head.csid >= 2 && head.csid <= 63)
	{
		bufsLen[0] = 1;
		bufs[0] = new uint8_t[1];	memset(bufs[0], 0, 1);

		bufs[0][0] = head.csid;
	}
	else if (head.csid >= 64 && head.csid <= 319)
	{
		bufsLen[0] = 2;
		bufs[0] = new uint8_t[2];	memset(bufs[0], 0, 2);

		//
		bufs[0][0] = 0x00;
		bufs[0][1] = head.csid - 64;
	}
	else if (head.csid >= 320 && head.csid <= 65599)
	{
		uint16_t num, bigNum;
		
		num = head.csid - 320;
		bigNum = HostToBig16(num);

		bufsLen[0] = 3;				memset(bufs[0], 0, 3);
		bufs[0] = new uint8_t[3];

		bufs[0][0] = 0x3f;
		memcpy(bufs[0] + 1, &bigNum, 2);
	}
	//FMT
	bufs[0][0] |= (head.fmt << 6);

	//message header
	switch (head.fmt)
	{
	case 0x00:
		bufsLen[1] = 11;
		bufs[1] = new uint8_t[11];

		bigNumber24 = HostToBig24(head.timestamp);	 tempPtr = (char*)(&bigNumber24); memcpy(bufs[1], tempPtr +1, 3);
		bigNumber24 = HostToBig24(head.messageLength); tempPtr = (char*)(&bigNumber24);	memcpy(bufs[1]+3, tempPtr + 1, 3);
															memcpy(bufs[1]+3+3,&head.messageTypeID,1);
		bigNumber32 = HostToBig32(head.messageStreamID);	memcpy(bufs[1] + 3 + 3 + 1, &bigNumber32, 4);
		break;
	case 0x01:
		bufsLen[1] = 7;
		bufs[1] = new uint8_t[7];

		bigNumber24 = HostToBig24(head.timestampDelta); tempPtr = (char*)(&bigNumber24); memcpy(bufs[1], tempPtr+1, 3);
		bigNumber24 = HostToBig24(head.messageLength);	tempPtr = (char*)(&bigNumber24); memcpy(bufs[1]+3, tempPtr + 1, 3);
															memcpy(bufs[1] + 3 + 3, &head.messageTypeID, 1);
		break;
	case 0x02:
		bufsLen[1] = 3;
		bufs[1] = new uint8_t[3];

		bigNumber24 = HostToBig24(head.timestampDelta); tempPtr = (char*)(&bigNumber24);	memcpy(bufs[1], tempPtr+1, 3);
		break;
	case 0x03:
		bufsLen[1] = 0;
		bufs[1] = NULL;
		break;
	default:
		break;
	}

	//extendedTimestamp
	if (head.extendedTimestamp != 0)
	{
		bufsLen[2] = 4;
		bufs[2] = new uint8_t[4];
		bigNumber32 = HostToBig32(head.extendedTimestamp);
		memcpy(bufs[2], &bigNumber32, 4);
	}
	else
	{
		bufsLen[2] = 0;
		bufs[2] = NULL;
	}

	for (i = 0; i < 3; i++)
		bufLength += bufsLen[i];

	buf = new uint8_t[bufLength];
	ptr = buf;
	for (i = 0; i < 3; i++)
	{
		memcpy(ptr,bufs[i],bufsLen[i]);
		ptr += bufsLen[i];
	}

	for (i = 0; i < 3; i++)
	{
		if (bufs[i] != NULL) delete[] bufs[i];
		bufs[i] = NULL;
		bufsLen[i] = 0;
	}
	
	*outLength = bufLength;
	return buf;
}