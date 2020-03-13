#include "Chunk.h"

CChunk::CChunk(CChunk* prev, const int chunkSize) :	m_BasicHeader(BasicHeaderType::INVALID),\
					m_MsgHeader(MessageHeaderType::INVALID),\
					m_ExTHeader(ExtendedTimestampType::INVALID),\
					m_Prev(prev),m_ChunkSize(chunkSize),m_ChunkDataLen(0)
{

}

CChunk::~CChunk()
{

}

int CChunk::GetByteLength(BasicHeaderType baseType)
{
	int length = 0;
	switch (baseType)
	{
	case BASE0:
		length = 1;
		break;
	case BASE1:
		length = 2;
		break;
	case BASE2:
		length = 3;
		break;
	default:
		break;
	}
	return length;
}

int CChunk::GetByteLength(MessageHeaderType msgType)
{
	int length = 0;

	switch (msgType)
	{
	case MSG0:
		length = 0;
		break;
	case MSG1:
		length = 3;
		break;
	case MSG2:
		length = 7;
		break;
	case MSG3:
		length = 11;
		break;
	default:
		break;
	}

	return length;
}

int CChunk::GetByteLength(ExtendedTimestampType extType)
{
	int length = 0;

	switch (extType)
	{
	case EXT0:
		length = 0;
		break;
	case EXT1:
		length = 4;
		break;
	default:
		break;
	}

	return length;
}

CChunk* CChunk::DeMultiplexing(CChunk* pPrev, const int chunkSize,char* buff, const int buffLen, int* outChunkLen)
{
	CChunk* pChunk = NULL;
	int result = SAR_FAILURE;
	int length = 0;

	pChunk = new CChunk;
	result = pChunk->Demux(buff,buffLen,&length);
	if (result != SAR_OK)
	{
		pChunk->Destory();
		pChunk = NULL;
		*outChunkLen = 0;
	}
	else 
		*outChunkLen = length;

	return pChunk;
}

void CChunk::Destory()
{
	delete this;
}

BasicHeaderType CChunk::GetBaseHeaderType()
{
	return m_BasicHeader;
}

MessageHeaderType CChunk::GetMessageHeaderType()
{
	return m_MsgHeader;
}

ExtendedTimestampType CChunk::GetExtendedTimestamp()
{
	return m_ExTHeader;
}

int CChunk::Demux(char* buff, const int buffLen, int* chunkLen)
{
	int basicLen = 0, msgLen = 0,extLen = 0;
	int basicRet = SAR_FAILURE , msgRet = SAR_FAILURE , extRet = SAR_FAILURE;
	int offset = 0;

	basicRet = DemuxBaseHeader(buff + offset,buffLen - offset,&basicLen);
	if (basicRet != SAR_OK)
		
basic_err:
	*chunkLen = 0;
	return basicRet;
msg_err:
	*chunkLen = 0;
	return msgRet;
ext_err:
	*chunkLen = 0;
	return extRet;
data_err:
	*chunkLen = 0;
	return DATA_LACK;
}

int CChunk::DemuxBaseHeader(char* buff, const int buffLen, int* outBasicLen)
{

}

int CChunk::DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen)
{

}

int CChunk::DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen)
{

}