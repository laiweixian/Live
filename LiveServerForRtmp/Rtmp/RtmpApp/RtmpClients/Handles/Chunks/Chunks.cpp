#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks(string appName, uint32_t chunkSize) :m_Application(appName), m_ChunkSize(chunkSize)
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

int CChunks::AbortMessage(uint32_t csid)
{
	return -1;
}