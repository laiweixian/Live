#include "stdafx.h"
#include "Chunking.h"


CChunking::CChunking():m_DeltaTS(0)
{
	memset(&m_MsgHeader, 0, sizeof(CBaseMessage::Header));
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

uint8_t* CChunking::Encode(uint32_t* outLength)
{
	auto it = m_Chunks.begin();
	uint8_t *buf = NULL, *ptr = NULL;
	uint32_t bufLength = 0;
	

	for (it = m_Chunks.begin(); it != m_Chunks.end(); it++)
	{
		bufLength += (*it).head.length;
		bufLength += (*it).payload.length;
	}

	buf = new uint8_t[bufLength];
	ptr = buf;
	for (it = m_Chunks.begin(); it != m_Chunks.end(); it++)
	{
		memcpy(ptr, (*it).head.buf, (*it).head.length); ptr += (*it).head.length;
		memcpy(ptr, (*it).payload.buf, (*it).payload.length); ptr += (*it).payload.length;
	}

	*outLength = bufLength;
	return buf;
}

void CChunking::Encode(CBaseMessage* curr, const uint32_t chunkSize)
{
	uint32_t totalLength = curr->GetHeader().payloadLength,length = 0;
	auto it = m_ChunkHeads.begin();
	CChunkHeader::Head head;
	uint8_t *ptr = curr->GetPayload().buf;
	Chunk chunk = {0};

	for (it = m_ChunkHeads.begin(); it != m_ChunkHeads.end(); it++)
	{
		head = *it;

		//header
		chunk.head.buf = CChunkHeader::Encode(head, &chunk.head.length);

		//
		length = totalLength > chunkSize ? chunkSize : totalLength;
		chunk.payload.buf = new uint8_t[length];
		chunk.payload.length = length;
		memcpy(chunk.payload.buf,ptr,length);

		ptr += length;
		totalLength -= length;

		m_Chunks.push_back(chunk);
	}
	
}

void CChunking::Set(CChunking* prev, CBaseMessage* curr, uint32_t chunkSize)
{
	//分析每一个chunk头
	const uint32_t chunkCount = ceil(curr->GetHeader().payloadLength / chunkSize);
	
	SetFirstChunk(prev, curr);
	SetChunk4(chunkCount - 1);
	Encode(curr, chunkSize);
}



void CChunking::SetFirstChunk(CChunking* prev, CBaseMessage* curr)
{
	m_MsgHeader = curr->GetHeader();
	const uint8_t fType = CheckFirstHeader(prev, curr);
	switch (fType)
	{
	case 0x00:
		SetFirstChunk0(prev,curr);
		break;
	case 0x01:
		SetFirstChunk1(prev, curr);
		break;
	case 0x02:
		SetFirstChunk2(prev, curr);
		break;
	case 0x03:
		SetFirstChunk3(prev, curr);
		break;
	default:
		break;
	}
	
}

uint8_t CChunking::CheckFirstHeader(CChunking* prev, CBaseMessage* curr)
{
	CBaseMessage::Header prevMsgHeader;
	CChunkHeader::Head prevChunkHeader;
	uint8_t fType = 0xff;

	if (prev == NULL)
		fType = 0x00;
	else
	{
		prevChunkHeader = prev->m_ChunkHeads.at(0);
		prevMsgHeader = prev->m_MsgHeader;

		if (prevMsgHeader.msgType == m_MsgHeader.msgType && prevMsgHeader.payloadLength == m_MsgHeader.payloadLength && prevMsgHeader.msid == m_MsgHeader.msid)
		{
			//0x02 or 0x03
			if (m_DeltaTS == 0)
			{
				m_DeltaTS = m_MsgHeader.timestamp - prevMsgHeader.timestamp;
				fType = 0x02;
			}
			else
			{
				fType = 0x03;
			}

		}
		else
			fType = 0x00;
	}

	return fType;
}

void CChunking::SetFirstChunk0(CChunking* prev, CBaseMessage* curr)
{
	//
	CChunkHeader::Head first = {0};
	CChunkHeader::Head prevChunkHeader = prev->m_ChunkHeads.at(prev->m_ChunkHeads.size()-1);

	first.fmt = 0x00;
	if (prev == NULL)
		first.csid = 2;
	else
		first.csid = prevChunkHeader.csid + 1;
	
	first.timestamp = m_MsgHeader.timestamp;
	first.messageLength = m_MsgHeader.payloadLength;
	first.messageTypeID = m_MsgHeader.msgType;
	first.messageStreamID = m_MsgHeader.msid;
	
	m_ChunkHeads.push_back(first);
}

void CChunking::SetFirstChunk1(CChunking* prev, CBaseMessage* curr)
{
	//标准rtmp协议的示例中没有使用
	return;
}

void CChunking::SetFirstChunk2(CChunking* prev, CBaseMessage* curr)
{
	CChunkHeader::Head first = { 0 };
	CChunkHeader::Head prevChunkHeader = prev->m_ChunkHeads.at(prev->m_ChunkHeads.size() - 1);

	first.fmt = 0x02;
	first.csid = prevChunkHeader.csid + 1;

	first.timestampDelta = m_DeltaTS;

	m_ChunkHeads.push_back(first);
}

void CChunking::SetFirstChunk3(CChunking* prev, CBaseMessage* curr)
{
	CChunkHeader::Head first = { 0 };
	CChunkHeader::Head prevChunkHeader = prev->m_ChunkHeads.at(prev->m_ChunkHeads.size() - 1);

	first.fmt = 0x03;
	first.csid = prevChunkHeader.csid + 1;

	m_ChunkHeads.push_back(first);
}

void CChunking::SetChunk4(uint32_t count)
{
	CChunkHeader::Head first = { 0 };
	uint32_t csid = m_ChunkHeads.at(0).csid;
	int i = 0;

	if (count == 0)
		return;

	for (i=0;i<count;i++)
	{
		first.fmt = 0x03;
		first.csid = csid + 1;
		csid++;
		m_ChunkHeads.push_back(first);
	}
	
}
