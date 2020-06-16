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

void CChunks::HandleSetChunkSize(CBaseMessage* pMsg)
{

}

void CChunks::HandleAcknowledgement(CBaseMessage* pMsg)
{

}
void CChunks::HandleWindowAcknowledgementSize(CBaseMessage* pMsg)
{

}
void CChunks::HandleSetPeerBandwidth(CBaseMessage* pMsg)
{

}
void CChunks::HandleUserControlMessages(CBaseMessage* pMsg)
{

}
void CChunks::HandleCommandMessage(CBaseMessage* pMsg, const bool isVersion3)
{

}
void CChunks::HandleDataMessage(CBaseMessage* pMsg, const bool isVersion3 )
{

}
void CChunks::HandleSharedObjectMessage(CBaseMessage* pMsg, const bool isVersion3)
{

}

void CChunks::HandleAudioMessage(CBaseMessage* pMsg)
{

}

void CChunks::HandleVideoMessage(CBaseMessage* pMsg)
{

}

void CChunks::HandleAggregateMessage(CBaseMessage* pMsg)
{

}

