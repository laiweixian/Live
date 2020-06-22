#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(uint32_t chunkSize,CInstanceManager* appInstance) : \
				 m_ChunkSize(chunkSize),m_AppInstance(appInstance)
{

}

CChunks::~CChunks()
{
	
}

uint32_t CChunks::GetChunkSize()
{
	return m_ChunkSize;
}

int CChunks::HandleMessage(CBaseMessage* pMsg)
{
	return CRtmpMessage::HandleMessage(pMsg);
}

