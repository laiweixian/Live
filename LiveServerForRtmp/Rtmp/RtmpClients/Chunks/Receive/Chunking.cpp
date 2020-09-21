#include "stdafx.h"
#include "Chunking.h"


CChunking::CChunking() :m_DeltaTS(0) , m_MsgHeader({0}),m_Csid(2)
{

}


CChunking::~CChunking()
{
}



CChunking* CChunking::Create(CChunking* prev, CBaseMessage* curr, uint32_t chunkSize)
{
	CChunking* pChunk = NULL;
	pChunk = new CChunking;

	pChunk->Set(prev, curr, chunkSize);
	return pChunk;
}

void CChunking::Destroy()
{
	delete this;
}

uint8_t* CChunking::GetChunksBuffer(uint32_t* outLength)
{
	auto it = m_Chunks.begin();
	uint8_t *buf = NULL, *ptr = NULL;
	uint32_t bufLength = 0;
	
	for (it = m_Chunks.begin(); it != m_Chunks.end(); it++)
	{
		bufLength += it->head.length;
		bufLength += it->payload.length;
	}

	buf = new uint8_t[bufLength];
	ptr = buf;
	for (it = m_Chunks.begin(); it != m_Chunks.end(); it++)
	{
		memcpy(ptr, it->head.buf, it->head.length); ptr += it->head.length;
		memcpy(ptr, it->payload.buf, it->payload.length); ptr += it->payload.length;
	}

	*outLength = bufLength;
	return buf;
}



void CChunking::Set(CChunking* prev, CBaseMessage* curr, uint32_t chunkSize)
{
	//分析每一个chunk头
	const float fC = chunkSize;
	const float fP = curr->GetHeader().payloadLength;
	const uint32_t chunkCount = ceil(fP/fC);
	Chunk chunk = {0};
	int i = 0;

	for (i = 0; i < chunkCount; i++)
		m_Chunks.push_back(chunk);
	m_MsgHeader = curr->GetHeader();
	
	SetChunkHead(prev);
	SetChunkPayload(curr, chunkSize);
}

void CChunking::SetChunkPayload(CBaseMessage* curr, uint32_t chunkSize)
{
	auto it = m_Chunks.begin();

	CBaseMessage::Payload payload = curr->GetPayload();
	uint8_t *ptr = payload.buf;
	uint32_t totalLength = payload.bufSize;
	uint32_t max = 0;

	for (it = m_Chunks.begin(); it!= m_Chunks.end(); it++)
	{
		max = totalLength > chunkSize ? chunkSize : totalLength;
		
		it->payload.length = max;
		it->payload.buf = new uint8_t[max];
		memcpy(it->payload.buf,ptr,max);

		totalLength -= max;
		ptr += max;
	}


}

void CChunking::SetChunkHead(CChunking* prev)
{
	SetFirstChunkHead(prev);
	SetOtherChunkHead();
}

void CChunking::SetFirstChunkHead(CChunking* prev)
{
	uint8_t fmt = 0x00;
	uint32_t deltaTimestamp = 0;
	CChunkHeader::Head head = {0};
	uint8_t *headBuf = NULL; uint32_t headBufLength = 0;
	auto it = m_Chunks.begin();

	//message first chunk
	if (prev == NULL)
		fmt = 0x00;
	else
	{
		if (prev->m_MsgHeader.msgType == m_MsgHeader.msgType)
		{
			deltaTimestamp = m_MsgHeader.timestamp = prev->m_MsgHeader.timestamp;
			if (prev->m_DeltaTS == deltaTimestamp)
				fmt = 0x03;
			else
				fmt = 0x02;
			m_DeltaTS = deltaTimestamp;
		}
		else
		{
			fmt = 0x00;
		}
	}

	head.fmt = fmt;
	head.csid = GetNextCsid();

	//设置第一个chunk head
	switch (fmt)
	{
	case 0x00:
		head.timestamp = m_MsgHeader.timestamp;
		head.messageLength = m_MsgHeader.payloadLength;
		head.messageTypeID = m_MsgHeader.msgType;
		head.messageStreamID = m_MsgHeader.msid;
		break;
	case 0x01:
		break;
	case 0x02:
		head.timestampDelta = m_DeltaTS;
		break;
	case 0x03:
		break;
	default:
		break;
	}

	headBuf = CChunkHeader::Encode(head, &headBufLength);
	it->head.buf = headBuf;
	it->head.length = headBufLength;
}

void CChunking::SetOtherChunkHead()
{
	auto it = m_Chunks.begin();
	CChunkHeader::Head head = { 0 };
	const int count = m_Chunks.size();
	uint8_t *headBuf = NULL; uint32_t headBufLength = 0;

	if (count == 1)
		return;

	head.fmt = 0x03;
	head.csid = GetNextCsid();
	headBuf = CChunkHeader::Encode(head, &headBufLength);

	it++;
	for (;it<m_Chunks.end();it++)
	{
		it->head.length = headBufLength;
		it->head.buf = new uint8_t[headBufLength];
		memcpy(it->head.buf,headBuf,headBufLength);
	}
	
	delete[] headBuf;
	headBuf = NULL;
}


uint32_t CChunking::GetNextCsid()
{
	const uint32_t csid = m_Csid;
	m_Csid++;
	return csid;
}






