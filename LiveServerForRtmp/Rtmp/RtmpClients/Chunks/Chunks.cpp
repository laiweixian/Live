#include "Chunks.h"


#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks() 
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


int CChunks::AbortMessageHandle(CAbortMessage::Object *pObj)
{
	TRACE("Handle AbortMessage\n");
	return CReceiveChunk::Abort(pObj->csid);
}

int CChunks::SetChunkSizeHandle(CSetChunkSize::Object *pObj)
{
	TRACE("Handle SetChunkSize\n");
	ChangeChunkSize(pObj->chunkSize);
	return 0;
}

int CChunks::Send2MySelf(CBaseMessage* pMsg)
{
	return CSendMessage::Send2MySelf(pMsg);
}

uint32_t CChunks::GetStreamID()
{
	return 0;
}

