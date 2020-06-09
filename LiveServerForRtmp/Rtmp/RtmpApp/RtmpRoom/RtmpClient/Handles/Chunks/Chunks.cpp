#include "Chunks.h"

#define DELETE_PTR(ptr)	if(ptr){delete ptr; ptr = NULL;}
	
CChunks::CChunks( const uint32_t chunkSize) : m_ChunkSize(chunkSize)
{

}

CChunks::~CChunks()
{
	
}


void CChunks::HandleSetChunkSize(CSetChunkSize* pMsg)
{
	if (!pMsg)	return ;
	const CSetChunkSize::Content content = pMsg->GetContent();

	m_ChunkSize = content.chunkSize;

	delete pMsg;
}

void CChunks::HandleAbortMessage(CAbortMessage* pMsg)
{
	if (!pMsg)	return;
	const CAbortMessage::Content content = pMsg->GetContent();
}

void CChunks::HandleAcknowledgement(CAcknowledgement* pMsg)
{
	if (!pMsg)	return;
	const CAcknowledgement::Content content = pMsg->GetContent();
}

void CChunks::HandleWindowAcknowledgementSize(CWindowAcknowledgementSize* pMsg)
{
	if (!pMsg)	return;
	const CWindowAcknowledgementSize::Content content = pMsg->GetContent();
}

void CChunks::HandleSetPeerBandwidth(CSetPeerBandwidth* pMsg)
{
	if (!pMsg)	return;
	const CSetPeerBandwidth::Content content = pMsg->GetContent();
}

void CChunks::HandleUserControlMessages(CUserControlMessages* pMsg)
{
	if (!pMsg)	return;
	const CUserControlMessages::Content content = pMsg->GetContent();
}

void CChunks::HandleCommandMessage(CCommandMessage* pMsg)
{
	if (!pMsg)	return;
	
}

void CChunks::HandleDataMessage(CDataMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleSharedObjectMessage(CSharedObjectMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleAudioMessage(CAudioMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleVideoMessage(CVideoMessage* pMsg)
{
	if (!pMsg)	return;
}

void CChunks::HandleAggregateMessage(CAggregateMessage* pMsg)
{
	if (!pMsg)	return;
}

uint32_t CChunks::GetChunkSize()
{
	return m_ChunkSize;
}