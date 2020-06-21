#include "ReceChunk.h"
#include "stdafx.h"
#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}

CReceiveChunk::CReceiveChunk() :m_Lastest(NULL)
{

}

CReceiveChunk::~CReceiveChunk()
{

}

int CReceiveChunk::OnChunks(uint8_t* src, const int srcLength)
{
	/*
	uint8_t buf[1024] = { 0 };
	int len = srcLength > 1024 ? 1024 : srcLength;

	memcpy(buf, src, len);

	write2file(TEXT("RTMP"),src,srcLength);

	return len;
	*/
	
	int length = ReceiveMessage(src, srcLength);
	write2file(TEXT("RTMP"),src,length);
	return length;

}

int CReceiveChunk::ReceiveMessage(uint8_t* src, const int srcLen)
{
	const uint32_t chunkSize = GetChunkSize();
	CBaseMessage *pMsg = NULL;
	int chunkLen = 0;
	
	pMsg = CBaseMessage::Create(m_Lastest, chunkSize,src,srcLen,&chunkLen);
	if (pMsg == NULL && chunkLen == -1)
		return 0;
	
	if (pMsg)
	{
		if (m_Lastest) m_Lastest->Destroy();
		m_Lastest =  pMsg;
	}
	else
	{
		chunkLen = m_Lastest->AppendChunk(src,srcLen);
		if (chunkLen == 0)
			return 0;
	}

	if (m_Lastest->Full())
		HandleMessage(m_Lastest);
	
	if (srcLen > chunkLen)
		return (chunkLen+ReceiveMessage(src+chunkLen,srcLen-chunkLen));
	else 
		return chunkLen;
}