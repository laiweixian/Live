#include "stdafx.h"
#include "AntiChunking.h"


CAntiChunking::CAntiChunking(uint32_t chunkSize):m_ChunkSize(chunkSize)
{
}


CAntiChunking::~CAntiChunking()
{
}

CAntiChunking* CAntiChunking::Create(CAntiChunking* prev, uint32_t chunkSize, uint8_t* chunkBuf, const uint32_t chunkBufLen, int *outChunkLen)
{
	CAntiChunking* pNew = NULL;
	CChunkHeader *pHead = NULL;
	CChunkHeader::Head head;
	int headerLen = 0, dataLen = 0;
	bool newMsg = false;
	int msgLength = 0;

	pHead = CChunkHeader::Parse(chunkBuf, chunkBufLen, &headerLen);
	if (pHead == NULL)
		goto shortData;

	head = pHead->GetHead();
	switch (head.fmt)
	{
	case 0x00:
		newMsg = true;
		break;
	case 0x01:
		newMsg = true;
		pHead->CopyFrom(prev->m_Header);
		break;
	case 0x02:
		newMsg = true;
		pHead->CopyFrom(prev->m_Header);
		break;
	case 0x03:
		if (prev->Legal())
		{
			newMsg = true;
			pHead->CopyFrom(prev->m_Header);
		}
		else
		{
			newMsg = false;
		}
		break;
	}

	if (newMsg == false)
		goto noNew;

	msgLength = pHead->GetHead().messageLength;
	dataLen = chunkSize > msgLength ? msgLength : chunkSize;

	if ((dataLen + headerLen) > chunkBufLen)
		goto shortData;

	pNew = new CAntiChunking(chunkSize);
	pNew->SetFirstChunk(pHead, chunkBuf + headerLen, dataLen);
	*outChunkLen = headerLen + dataLen;
	return pNew;

noNew:
	if (pHead) delete pHead;
	*outChunkLen = 0;
	return NULL;

shortData:
	if (pHead) delete pHead;
	*outChunkLen = -1;
	return NULL;
}

void CAntiChunking::Destroy()
{
	delete this;
}

int CAntiChunking::AppendChunk(uint8_t* chunkBuf, const uint32_t chunkBufLen)
{
	CChunkHeader *pHead = NULL;
	int headerLen = 0, dataLen = 0;
	CChunkHeader::Head head;
	int leftLength = 0;

	if (Legal() == true)
		goto full;

	pHead = CChunkHeader::Parse(chunkBuf, chunkBufLen, &headerLen);
	if (pHead == NULL)
		goto shortData;

	head = pHead->GetHead();
	if (head.fmt != 0x03)
		goto err;

	//chunk data len
	leftLength = (m_Payload.buf + m_Payload.bufSize - m_Payload.ptr);
	dataLen = leftLength > m_ChunkSize ? m_ChunkSize : leftLength;

	if ((headerLen + dataLen) > chunkBufLen)
		goto shortData;

	memcpy(m_Payload.ptr, chunkBuf + headerLen, dataLen);
	m_Payload.ptr += dataLen;

	return (dataLen + headerLen);

shortData:
	return 0;
full:
	return 0;
err:
	return -1;
}



void CAntiChunking::SetFirstChunk(CChunkHeader* pHead, uint8_t *chunkPayloadBuf, int chunkPayloadBufLen)
{
	CChunkHeader::Head head;

	m_Header = pHead;
	head = m_Header->GetHead();

	CBaseMessage::SetHeader(head.messageTypeID, head.messageLength, head.timestamp + head.timestampDelta, head.messageStreamID);
	CBaseMessage::AppendPayload(chunkPayloadBuf, chunkPayloadBufLen);
}