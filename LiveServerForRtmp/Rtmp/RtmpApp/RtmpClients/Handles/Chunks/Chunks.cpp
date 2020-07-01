#include "Chunks.h"


#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(uint32_t chunkSize,CInstanceManager* appInstance) : \
				 m_ChunkSize(chunkSize), m_InstanceManager(appInstance),m_Instance(NULL)
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
	return CReceiveMessage::HandleMessage(pMsg);
}

