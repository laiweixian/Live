#include "BaseMessage.h"


CBaseMessage::CBaseMessage(uint32_t chunkSize) :\
						 m_Header(NULL),m_ChunkSize(chunkSize), m_Payload({NULL,0})
{
	
}

CBaseMessage::~CBaseMessage()
{
	
}

CBaseMessage* CBaseMessage::CreateForChunk(CBaseMessage* prev, uint32_t chunkSize, uint8_t* src, const uint32_t srcLen, int *outChunkLen)
{
	CBaseMessage* pMsg = NULL;
	CChunkHeader *pHead = NULL;
	CChunkHeader::Head head;
	int headerLen = 0, dataLen = 0;
	bool newMsg = false;
	int msgLength = 0;

	pHead = CChunkHeader::Parse(src, srcLen, &headerLen);
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
		pHead->CopyFrom(prev->GetHead());
		break;
	case 0x02:		
		newMsg = true;
		pHead->CopyFrom(prev->GetHead());
		break;
	case 0x03:		
		if (prev->Full())
		{
			newMsg = true;
			pHead->CopyFrom(prev->GetHead());
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

	if ((dataLen+headerLen) > srcLen)
		goto shortData;

	pMsg = new CBaseMessage(chunkSize);
	pMsg->SetFirstChunk(pHead,src+headerLen,dataLen);

	*outChunkLen = headerLen + dataLen;
	return pMsg;

noNew:
	if (pHead) delete pHead;
	*outChunkLen = 0;
	return NULL;

shortData:
	if (pHead) delete pHead;
	*outChunkLen = -1;
	return NULL;
}

void CBaseMessage::Destroy()
{
	delete this;
}


void CBaseMessage::SetFirstChunk(CChunkHeader* pHead, uint8_t *data, int dataLen)
{
	CChunkHeader::Head head;

	m_Header = pHead;
	head = m_Header->GetHead();

	//alloc payload 
	m_Payload.bufSize = head.messageLength;
	m_Payload.buf = new uint8_t[m_Payload.bufSize];
	m_Payload.ptr = m_Payload.buf;

	memset(m_Payload.buf,0, m_Payload.bufSize);
	memcpy(m_Payload.ptr,data,dataLen);
	m_Payload.ptr += dataLen;
}

CBaseMessage::Payload* CBaseMessage::GetPayload()
{
	return (&m_Payload);
}

CChunkHeader* CBaseMessage::GetHead()
{
	return m_Header;
}

bool CBaseMessage::Full()
{
	return (m_Payload.buf + m_Payload.bufSize == m_Payload.ptr);
}


int CBaseMessage::AppendChunk(uint8_t* src, const uint32_t srcLen)
{
	CChunkHeader *pHead = NULL;
	int headerLen = 0, dataLen = 0;
	CChunkHeader::Head head;
	int leftLength = 0;

	if (Full() == true)
		goto full;

	pHead = CChunkHeader::Parse(src, srcLen, &headerLen);
	if (pHead == NULL)
		goto shortData;
	
	head = pHead->GetHead();
	if (head.fmt != 0x03)
		goto err;

	//chunk data len
	leftLength = (m_Payload.buf + m_Payload.bufSize - m_Payload.ptr);
	dataLen = leftLength > m_ChunkSize ? m_ChunkSize : leftLength;

	if ((headerLen + dataLen) > srcLen)
		goto shortData;

	memcpy(m_Payload.ptr,src+headerLen,dataLen);
	m_Payload.ptr += dataLen;

	return (dataLen + headerLen);

shortData:
	return 0;
full:
	return 0;
err:
	return -1;
}