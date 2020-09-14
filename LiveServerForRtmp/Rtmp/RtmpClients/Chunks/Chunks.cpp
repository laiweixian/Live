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

int CChunks::AbortMessageHandle(uint32_t csid)
{
	TRACE("Handle AbortMessage\n");
	return CReceiveChunk::Abort(csid);
}

int CChunks::SetChunkSizeHandle(uint32_t chunkSize)
{
	TRACE("Handle SetChunkSize\n");
	m_ChunkSize = chunkSize;
	return 0;
}
