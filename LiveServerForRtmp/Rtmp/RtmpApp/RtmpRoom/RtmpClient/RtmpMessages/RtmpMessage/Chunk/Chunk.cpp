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

	pChunk = new CChunk(pPrev,chunkSize);
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

int CChunk::Demux(char* buff, const int buffLen, int* outChunkLen)
{
	int headerLen = 0, dataLen = 0;
	int headerRet = SAR_FAILURE , dataRet = SAR_FAILURE;
	int offset = 0;

	headerRet = DemuxChunkHeader(buff,buffLen,&headerLen);
	if (headerRet != SAR_OK)
		goto header_err;
	offset += headerLen;

	dataRet = DemuxChunkData(buff+offset,buffLen-offset,&dataLen);
	if (dataRet != SAR_OK)
		goto data_err;
	offset += dataLen;
	
	*outChunkLen = offset;
	return SAR_OK;

header_err:
	*outChunkLen = 0;
	return headerRet;
data_err:
	*outChunkLen = 0;
	return dataRet;
}

int CChunk::DemuxChunkHeader(char* buff, const int buffLen, int* outChunkHeaderLen)
{
	int basicLen = 0, msgLen = 0,extLen = 0;
	int basicRet = SAR_FAILURE , msgRet = SAR_FAILURE , extRet = SAR_FAILURE;
	int offset = 0;

	basicRet = DemuxBaseHeader(buff + offset,buffLen - offset,&basicLen);
	if (basicRet != SAR_OK)
		goto basic_err;
	offset += basicLen;
	if (buffLen < offset)
		goto basic_err;

	msgRet = DemuxMsgHeader(buff + offset,buffLen-offset,&msgLen);
	if (msgRet != SAR_OK)
		goto msg_err;
	offset += msgLen;
	if (buffLen < offset)
		goto msg_err;

	extRet = DemuxExtendedTimestamp(buff+offset,buffLen-offset,&extLen);
	if (extRet != SAR_OK)
		goto ext_err;
	offset += extLen;
	if (buffLen < offset)
		goto ext_err;

	*outChunkHeaderLen = offset;
	return SAR_OK;
basic_err:
	*outChunkHeaderLen = 0;
	return basicRet;
msg_err:
	*outChunkHeaderLen = 0;
	return msgRet;
ext_err:
	*outChunkHeaderLen = 0;
	return extRet;
}

int CChunk::DemuxBaseHeader(char* buff, const int buffLen, int* outBasicLen)
{
	int offset ;
}

int CChunk::DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen)
{

}

int CChunk::DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen)
{

}

int CChunk::DemuxChunkData(char* buff, const int buffLen, int* outChunkDataLen)
{

}