#include "RtmpMessages.h"

CRtmpMessages::CRtmpMessages()
{

}

CRtmpMessages::~CRtmpMessages()
{

}

int CRtmpMessages::OnReceive(char *buff, const int buffLen)
{
	return DeMultiplexing(buff,buffLen);
}

int CRtmpMessages::DeMultiplexing(char *buff, const int buffLen)
{
	int ret ;

}

int CRtmpMessages::DeMultiplexingChunkHeader(char *buff, const int buffLen)
{
	int chunkHeaderLen = 0;
	CChunk *pChunkHeader = NULL;

	if (buff == NULL || buffLen <= 0)
		return 0;

	pChunkHeader = CChunk::DeMultiplexing(buff, buffLen, &chunkHeaderLen);
	if (pChunkHeader == NULL)
		return 0;

	DeMultiplexingChunkData(pChunkHeader,buff+chunkHeaderLen,buffLen-chunkHeaderLen);
	return chunkHeaderLen;
}


int CRtmpMessages::DeMultiplexingChunkData( CChunk* pChunk,char *buff, const int buffLen)
{
	const MessageHeaderType msgType = pChunk->GetMessageHeaderType();
	const ChunkHeaderInfo info  = pChunk->GetInfo();
	auto it = m_ChunkInfors.begin();
	int chunkDataLen = 0;
	CRtmpMsg *pMsg = NULL;
	

	switch (msgType)
	{
	case MessageHeaderType::INVALID:
		pMsg = new CRtmpMsg(info.timestamp,info.message_length,info.message_type_id,info.message_stream_id);
		m_ChunkInfors.clear();
		break;
	case MessageHeaderType::MSG0:
		
		break;
	case MessageHeaderType::MSG1:
		break;
	case MessageHeaderType::MSG2:
		break;
	case MessageHeaderType::MSG3:
		break;
	default:
		break;
	}

	if (pMsg != NULL)
	{
		m_Msgs.push_back(pMsg);
	}


	return chunkDataLen;
}

