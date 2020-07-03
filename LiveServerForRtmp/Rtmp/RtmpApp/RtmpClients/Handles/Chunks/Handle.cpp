#include "Chunks.h"
#include "Rtmp/Util/RtmpUtils.h"
#include "Rtmp/RtmpApp/RtmpInstance/InstanceManager.h"

int CChunks::SetAbortMessage(uint32_t csid)
{
	return CReceiveChunk::Abort(csid);
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

int CChunks::SetAudioMessage(CRtmpMessage* pMsg)
{
	return -1;
}

int CChunks::SetVideoMessage(CRtmpMessage* pMsg)
{
	return -1;
}

int CChunks::SetConnect(const char* rtmpurl)
{
	char url[2048] = {0};
	RtmpUrl *pUrl = NULL;
	CRtmpInstance* pInstance = NULL;

	strcpy(url,rtmpurl);
	pUrl = ParseRtmpUrl(url);

	//
	pInstance = m_InstanceManager->Connect(pUrl->instance);
	if (pInstance == NULL)
		return -1;
	m_Instance = pInstance;

	//send 

	return 0;
}