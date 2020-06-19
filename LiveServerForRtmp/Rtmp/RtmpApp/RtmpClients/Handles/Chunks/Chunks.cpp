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
	uint32_t chunkSize = 0;
	uint8_t buf[4] = {0};

	memcpy(buf,pMsg->GetData(),4);
	chunkSize = BigToHost32(buf);

	m_ChunkSize = chunkSize;
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
	bool v0 = isVersion3;

	write2file("command",pMsg->GetData(),pMsg->GetDataLength());
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

