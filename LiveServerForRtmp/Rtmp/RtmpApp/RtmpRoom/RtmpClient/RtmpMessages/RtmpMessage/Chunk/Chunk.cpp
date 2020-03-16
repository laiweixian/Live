#include "Chunk.h"

CChunk::CChunk() :	m_BasicHeader(BasicHeaderType::INVALID),\
					m_MsgHeader(MessageHeaderType::INVALID),\
					m_ExT(ExtendedTimestampType::INVALID)
{
	m_Info = {0};
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

CChunk* CChunk::DeMultiplexing(char* buff, const int buffLen, int* outChunkLen)
{
	CChunk* pChunk = NULL;
	int result = SAR_FAILURE;
	int length = 0;

	pChunk = new CChunk();
	result = pChunk->Demux(buff,buffLen,&length);
	if (result != SAR_OK)
	{
		pChunk->Restore();
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

ExtendedTimestampType CChunk::GetExtendedTimestampType()
{
	return m_ExT;
}

ChunkHeaderInfo CChunk::GetInfo()
{
	return m_Info;
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

	
	
	*outChunkLen = offset;
	return SAR_OK;

header_err:
	*outChunkLen = 0;
	return headerRet;
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
	int basicLen = 0, csidLen = 0;
	
	if (buffLen < 1)
		return DATA_LACK;

	const char fmt = (*buff) >> 6;
	const char csid = ((*buff) << 2) >> 2;
	const char max6Bits = (0xff << 2) >> 2;
	const char min6Bits = (0x00 << 2) >> 2;

	switch (fmt)
	{
	case 0x00:	m_MsgHeader = MSG0; break;
	case 0x01:	m_MsgHeader = MSG1; break;
	case 0x02:	m_MsgHeader = MSG2; break;
	case 0x03:	m_MsgHeader = MSG3;	break;
	default:						break;
	}

	switch (csid)
	{
	case max6Bits:	m_BasicHeader = BASE2; 	 break;
	case min6Bits:  m_BasicHeader = BASE1;	 break;
	default:		m_BasicHeader = BASE0;	 break;
	}

	basicLen = CChunk::GetByteLength(m_BasicHeader);
	csidLen = basicLen;
	if (buffLen < basicLen)
		return DATA_LACK;
	if (csid == 0 || csid == 1)
		return INVALID_CHUNK;

	SetFMT(buff);
	SetCSID(buff,csidLen);
	*outBasicLen = basicLen;
	return SAR_OK;
}

int CChunk::DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen)
{
	const int timestampLen = 3, timestampDeltaLen = 3 ,messageLengthLen = 3, messageTypeIDLen = 1, messageStreamIDLen = 4;
	const int msgLen = CChunk::GetByteLength(m_MsgHeader);
	int offset = 0;
	if (buffLen < msgLen)
		return DATA_LACK;

	switch (m_MsgHeader)
	{
	case INVALID:
		break;
	case MSG0:
		SetTimestamp(buff);						offset += timestampLen;
		SetMessageLength(buff + offset);		offset += messageLengthLen;
		SetMessageTypeID(buff + offset);		offset += messageTypeIDLen;
		SetMessageStreamID(buff + offset);		offset += messageStreamIDLen;	
		break;
	case MSG1:
		SetTimestampDelta(buff);				offset += timestampDeltaLen;
		SetMessageLength(buff + offset);		offset += messageLengthLen;
		SetMessageTypeID(buff + offset);		offset += messageTypeIDLen;
	case MSG2:
		SetTimestampDelta(buff);				offset += timestampDeltaLen;
		break;
	case MSG3:
		break;
	default:
		break;
	}

	*outMsgLen = msgLen;
	return SAR_OK;
}

int CChunk::DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen)
{
	const int basicLen = CChunk::GetByteLength(m_BasicHeader);

	int len = 0;
	int extLen = 0;
	

	if (m_MsgHeader == MSG3)
	{
		m_ExT = EXT0;
	}
	else
	{
		if (m_Info.timestamp == 0xffffff || m_Info.timestamp_delta == 0xffffff)
			m_ExT = EXT1;
		else 
			m_ExT = EXT0;
	}

	extLen = CChunk::GetByteLength(m_ExT);
	if (buffLen < extLen)
		return DATA_LACK;

	SetExtendedTimestamp(buff, extLen);
	
	*outExtLen = extLen;
	return SAR_OK;
}



void CChunk::Restore()
{
	m_Prev = NULL;
	m_ChunkSize = 0;
	m_ChunkDataLen = 0;
	m_BasicHeader = BasicHeaderType::INVALID;
	m_MsgHeader = MessageHeaderType::INVALID;
	m_ExT = ExtendedTimestampType::INVALID;
	
	m_Info = { 0 };
}

int CChunk::GetHeaderLength()
{
	const int basicLen = CChunk::GetByteLength(m_BasicHeader);
	const int msgLen = CChunk::GetByteLength(m_MsgHeader);
	const int extLen = CChunk::GetByteLength(m_ExT);

	return (basicLen + msgLen + extLen);
}

void CChunk::SetFMT(void *buff, const int buffLen)
{
	uint8_t fmt ;
	
	memcpy(&fmt,buff, buffLen);

	fmt = (fmt >> 6);
	m_Info.fmt = fmt;
	m_FieldTypes.push_back(FMT);
}

void CChunk::SetCSID(void *buff, const int buffLen)
{
	char csid[3] = { 0 };
	uint32_t csidNumber = 0;

	memcpy(csid,buff,buffLen);
	if (buffLen == CChunk::GetByteLength(BASE0))
	{
		csidNumber = csid[0];
	}
	else if (buffLen == CChunk::GetByteLength(BASE1))
	{
		csidNumber = csid[1] + 64;
	}
	else if (buffLen == CChunk::GetByteLength(BASE2))
	{
		csidNumber = (csid[2] * 256) + csid[1] + 64;
	}
	else 
		return ;
	m_Info.csid = csidNumber;
	m_FieldTypes.push_back(CSID);
}

void CChunk::SetTimestamp(void *buff, const int buffLen)
{
	uint32_t ts; 

	memcpy(&ts,buff,buffLen);
	ts = ::BigToHost24(&ts);
	
	m_Info.timestamp = ts;
	m_FieldTypes.push_back(TIMESTAMP);
}

void CChunk::SetTimestampDelta(void *buff, const int buffLen)
{
	uint32_t tsDelta;

	memcpy(&tsDelta, buff, buffLen);
	tsDelta = ::BigToHost24(&tsDelta);

	m_Info.timestamp_delta = tsDelta;
	m_FieldTypes.push_back(TIMESTAMP_DELTA);
}

void CChunk::SetMessageLength(void *buff, const int buffLen)
{
	uint32_t msgLength ;

	memcpy(&msgLength,buff,buffLen);
	msgLength = ::BigToHost24(&msgLength);

	m_Info.message_length = msgLength;
	m_FieldTypes.push_back(MESSAGE_LENGTH);
}

void CChunk::SetMessageTypeID(void *buff, const int buffLen)
{
	uint8_t msgTypeID ; 

	memcpy(&msgTypeID,buff,buffLen);

	m_Info.message_type_id = msgTypeID;
	m_FieldTypes.push_back(MESSAGE_TYPE_ID);
}

void CChunk::SetMessageStreamID(void *buff, const int buffLen)
{
	uint32_t msgStreamID; 

	memcpy(&msgStreamID,buff,buffLen);

	msgStreamID = ::BigToHost32(&msgStreamID);
	m_Info.message_stream_id = msgStreamID;
	m_FieldTypes.push_back(MESSAGE_STREAM_ID);
}

void CChunk::SetExtendedTimestamp(void *buff, const int buffLen)
{
	uint32_t exTs ;

	if (buffLen == 0)
	{
		
	}
	else
	{
		memcpy(&exTs, buff, buffLen);
		exTs = ::BigToHost32(&exTs);
		m_Info.extended_timestamp = exTs;
		m_FieldTypes.push_back(EXTENDED_TIMESTAMP);
	}
	
}
