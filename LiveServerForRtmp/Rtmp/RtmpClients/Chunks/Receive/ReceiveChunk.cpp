
#include "stdafx.h"
#include "ReceiveChunk.h"
#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}

CReceiveChunk::CReceiveChunk() :m_Lastest(NULL),m_ReceiveChunkSize(128)
{

}

CReceiveChunk::~CReceiveChunk()
{

}

CBaseMessage* CReceiveChunk::Receive(uint8_t* src, const int srcLen,int *outChunkLength)
{
	const uint32_t chunkSize = m_ReceiveChunkSize;
	CAntiChunking *pMsg = NULL;
	int chunkLen = 0;
	int result = 0;
	static int count = 1;
	
	pMsg = CAntiChunking::Create(m_Lastest, chunkSize,src,srcLen,&chunkLen);
		
	if (pMsg)
	{
		TRACE("new Message,type:%d,count:%d\n",pMsg->GetHeader().msgType,count++);
		if (m_Lastest) m_Lastest->Destroy();
		m_Lastest =  pMsg;
	}
	else
	{
		chunkLen = m_Lastest->AppendChunk(src,srcLen);
	}

	*outChunkLength = chunkLen;
	return m_Lastest;
}

int CReceiveChunk::Abort(uint32_t csid)
{
	return -1;
}

int CReceiveChunk::ChangeChunkSize(uint32_t chunkSize)
{
	m_ReceiveChunkSize = chunkSize;
	return 0;
}