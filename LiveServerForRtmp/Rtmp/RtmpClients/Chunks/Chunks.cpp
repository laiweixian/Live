#include "Chunks.h"


#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(uint32_t chunkSize) : \
				 m_ChunkSize(chunkSize)
{

}

CChunks::~CChunks()
{
	
}

int CChunks::OnChunks(uint8_t* src, const int srcLength)
{
	CAntiChunking* pMsg = NULL;
	int totalLen = 0, chunkLen = 0;
	int result = 0;


	while (totalLen < srcLength)
	{
		chunkLen = 0;
		pMsg = Receive(src + totalLen, srcLength - totalLen, &chunkLen);
		if (pMsg == NULL)
		{
			TRACE("Receive Chunk is Null\n");
			break;
		}
			
		totalLen += chunkLen;
		if (pMsg->Legal())
		{
			result = HandleMessage(pMsg);
			if (result != 0)
				TRACE("RtmpMessage Handle Failure,result:%d,id:%d\n", result, pMsg->GetHeader().msgType);
		}
		
	}
	
	return totalLen;
}

uint32_t CChunks::GetChunkSize()
{
	return m_ChunkSize;
}

int CChunks::AbortMessageHandle(CAbortMessage::Object *pObj)
{
	TRACE("Handle AbortMessage\n");
	return CReceiveChunk::Abort(pObj->csid);
}

int CChunks::SetChunkSizeHandle(CSetChunkSize::Object *pObj)
{
	TRACE("Handle SetChunkSize\n");
	m_ChunkSize = pObj->chunkSize;
	return 0;
}

