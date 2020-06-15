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


void CChunks::HandleSetChunkSize(CSetChunkSize* pMsg)
{
	if (!pMsg)	return ;
	const CSetChunkSize::Content content = pMsg->GetContent();

	m_ChunkSize = content.chunkSize;

	delete pMsg;
}


void CChunks::HandleAcknowledgement(CAcknowledgement* pMsg)
{

}
void CChunks::HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg)
{

}
void CChunks::HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg)
{

}
void CChunks::HandleUserControlMessages(CUserControlMessages* pMsg)
{

}
void CChunks::HandleCommandMessage(CCommandMessage* pMsg)
{

}
void CChunks::HandleDataMessage(CDataMessage* pMsg)
{

}
void CChunks::HandleSharedObjectMessage(CSharedObjectMessage* pMsg)
{

}
void CChunks::HandleAudioMessage(CAudioMessage* pMsg)
{

}
void CChunks::HandleVideoMessage(CVideoMessage* pMsg)
{

}
void CChunks::HandleAggregateMessage(CAggregateMessage* pMsg)
{

}


