#include "stdafx.h"
#include "Chunking.h"


CChunking::CChunking()
{
}


CChunking::~CChunking()
{
}

uint8_t* CChunking::Create(CBaseMessage* prev, CBaseMessage* cur, uint32_t chunkSize, uint32_t *outLength)
{
	uint8_t *chunksBuf = NULL;
	uint32_t chunksBufLen = 0;
	const uint32_t chunkCount = ceil(cur->GetHeader().payloadLength / chunkSize);	//����ȡ����
	int i = 0;
	uint8_t* chunkHeader[] = {0};


	chunksBufLen += cur->GetPayload().bufSize;

	if (prev->GetHeader().msgType == cur->GetHeader().msgType)
	{
		//����

	}
	

	*outLength = chunksBufLen;
	return chunksBuf;
}
