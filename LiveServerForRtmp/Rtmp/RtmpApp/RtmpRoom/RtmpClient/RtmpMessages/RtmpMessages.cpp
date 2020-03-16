#include "RtmpMessages.h"

CRtmpMessages::CRtmpMessages()
{

}

CRtmpMessages::~CRtmpMessages()
{

}

int CRtmpMessages::OnReceive(char *buff, const int buffLen)
{
	return DeMultiplexingChunk(buff,buffLen);
}

int CRtmpMessages::DeMultiplexingChunk(char *buff, const int buffLen)
{
	int chunkHeaderLen = 0, chunkDataLen = 0;
	int ret = SAR_FAILURE;
	CChunk *pChunkHeader = NULL ,*pPrevChunk = NULL;
	CRtmpMessage *pMsg = NULL , *pPreMsg = NULL;
	uint32_t ts = 0,tsDelta = 0, msgLen = 0, msgStreamID = 0;
	uint8_t msgTypeID = 0;
	auto itChunk = m_Chunks.begin();
	auto itMsg = m_Msgs.begin();

	if (buff == NULL || buffLen <= 0)
		return 0;

	pChunkHeader = CChunk::DeMultiplexing(buff, buffLen,&chunkHeaderLen);
	if (pChunkHeader == NULL)
		return 0;
	 


	return;
}

