
#include "stdafx.h"
#include "ReceiveChunk.h"
#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}

CReceiveChunk::CReceiveChunk() :m_Lastest(NULL)
{

}

CReceiveChunk::~CReceiveChunk()
{

}

CBaseMessage* CReceiveChunk::Receive(uint8_t* src, const int srcLen,int *outChunkLength)
{
	const uint32_t chunkSize = GetChunkSize();
	CBaseMessage *pMsg = NULL;
	int chunkLen = 0;
	int result = 0;
	
	pMsg = CBaseMessage::Create(m_Lastest, chunkSize,src,srcLen,&chunkLen);
	if (pMsg == NULL && chunkLen == -1)
		goto NoEnough;
		
	if (pMsg)
	{
		if (m_Lastest) m_Lastest->Destroy();
		m_Lastest =  pMsg;
	}
	else
	{
		chunkLen = m_Lastest->AppendChunk(src,srcLen);
		if (chunkLen == 0)
			goto NoEnough;
	}

	*outChunkLength = chunkLen;
	if (m_Lastest->Full())
		return m_Lastest;
	return NULL;

NoEnough:
	*outChunkLength = 0;
	return NULL;
}

int CReceiveChunk::Abort(uint32_t csid)
{
	return -1;
}