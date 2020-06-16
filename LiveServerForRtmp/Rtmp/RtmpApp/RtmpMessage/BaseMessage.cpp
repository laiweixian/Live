#include "BaseMessage.h"


CBaseMessage::CBaseMessage() : m_Header(NULL)
{
	
}

CBaseMessage::~CBaseMessage()
{
	
}

CBaseMessage* CBaseMessage::Create(CBaseMessage* prev, uint32_t chunkSize, uint8_t* src, const uint32_t srcLen, int* outTotalLen)
{
	CChunkHeader *pHead = NULL;
	CChunkHeader::Head head;
	int headerLen = 0, dataLen = 0;
	bool newMsg = false;

	pHead = CChunkHeader::Parse(src, srcLen, &headerLen);
	if (pHead == NULL)
		goto fail;

	head = pHead->GetHead();
	switch (head.fmt)
	{
	case 0x00:
		newMsg = true;
		break;
	case 0x01:	
		newMsg = true;
		pHead->CopyFrom(prev->GetChunkHeader());
		break;
	case 0x02:		break;
	case 0x03:		break;
	}


	return;
fail:
	*outTotalLen = 0;
}

void CBaseMessage::Destroy()
{
	delete this;
}





