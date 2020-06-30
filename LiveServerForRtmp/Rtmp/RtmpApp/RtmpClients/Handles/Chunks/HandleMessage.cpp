#include "Chunks.h"
#include "Rtmp/Util/RtmpUtils.h"

int CChunks::SetAbortMessage(uint32_t csid)
{
	return CReceiveChunk::AbortMessage(csid);
}
int CChunks::SetSequenceNumber(uint32_t sequenceNumber)
{
	return -1;
}
int CChunks::SetWinAckSize(uint32_t winAckSize)
{
	return -1;
}

int CChunks::SetChunkSize(uint32_t chunkSize)
{
	m_ChunkSize = chunkSize;
	return 0;
}



int CChunks::SetAudioMessage(CBaseMessage* pMsg)
{
	return -1;
}

int CChunks::SetVideoMessage(CBaseMessage* pMsg)
{
	return -1;
}

int CChunks::SetConnect(const char* rtmpurl)
{
	char url[2048] = {0};
	RtmpUrl *pUrl = NULL;

	strcpy(url,rtmpurl);
	pUrl = ParseRtmpUrl(url);
	
	
	return -1;
}