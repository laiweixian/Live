#include "Chunk.h"

CChunk::CChunk() :	m_BasicHeader(BasicHeaderType::INVALID),\
					m_MsgHeader(MessageHeaderType::INVALID),\
					m_ExT(ExtendedTimestampType::INVALID)
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
	
	m_Fields.push_back(new ChunkHeaderField(FMT, buff, 1));
	m_Fields.push_back(new ChunkHeaderField(CSID, buff ,csidLen));
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
		m_Fields.push_back(new ChunkHeaderField(TIMESTAMP, buff, timestampLen));
		offset += timestampLen;
		m_Fields.push_back(new ChunkHeaderField(MESSAGE_LENGTH,buff+offset,messageLengthLen));
		offset += messageLengthLen;
		m_Fields.push_back(new ChunkHeaderField(MESSAGE_TYPE_ID,buff+offset, messageTypeIDLen));
		offset += messageTypeIDLen;
		m_Fields.push_back(new ChunkHeaderField(MESSAGE_STREAM_ID,buff+offset, messageStreamIDLen));
		offset += messageStreamIDLen;
		break;
	case MSG1:
		m_Fields.push_back(new ChunkHeaderField(TIMESTAMP_DELTA, buff, timestampDeltaLen));
		offset += timestampDeltaLen;
		m_Fields.push_back(new ChunkHeaderField(MESSAGE_LENGTH, buff + offset, messageLengthLen));
		offset += messageLengthLen;
		m_Fields.push_back(new ChunkHeaderField(MESSAGE_TYPE_ID, buff + offset, messageTypeIDLen));
		offset += messageTypeIDLen;
		break;
	case MSG2:
		m_Fields.push_back(new ChunkHeaderField(TIMESTAMP_DELTA, buff, timestampDeltaLen));
		offset += timestampDeltaLen;
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
	char timestamp[3] = {0};
	int len = 0;
	int extLen = 0;
	auto it = m_Fields.begin();

	if (m_MsgHeader == MSG3)
	{
		m_ExT = EXT0;
	}
	else
	{
		for (it = m_Fields.begin(); it != m_Fields.end(); it++)
		{
			if ((*it)->m_Type == TIMESTAMP || (*it)->m_Type == TIMESTAMP_DELTA)
			{
				(*it)->Copy(timestamp, &len);
				break;
			}
		}

		if (timestamp[0] == 0xff && timestamp[1] == 0xff && timestamp[2] == 0xff)
			m_ExT = EXT1;
		else
			m_ExT = EXT0;
	}

	extLen = CChunk::GetByteLength(m_ExT);
	if (buffLen < extLen)
		return DATA_LACK;


	m_Fields.push_back(new ChunkHeaderField(EXTENDED_TIMESTAMP,buff,extLen));
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
	
	auto it = m_Fields.begin();
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		delete (*it);
		(*it) = NULL;
	}

	m_Fields.clear();
}

int CChunk::GetHeaderLength()
{
	const int basicLen = CChunk::GetByteLength(m_BasicHeader);
	const int msgLen = CChunk::GetByteLength(m_MsgHeader);
	const int extLen = CChunk::GetByteLength(m_ExT);

	return (basicLen + msgLen + extLen);
}

int CChunk::GetFMT(uint8_t *pFmt)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	char fmt = 0;
	int len = 0;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == FMT)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&fmt, &len);

	memcpy(pFmt,&fmt,1);
	return 0;
}

int CChunk::GetCSID(uint32_t *pCsid)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t csidNumber = 0;
	char csid[3] = {0};
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == CSID)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;
	
	field->Copy(csid, &len);
	if (len == CChunk::GetByteLength(BASE0))
	{
		csidNumber = csid[0];
	}
	else if (len == CChunk::GetByteLength(BASE1))
	{
		csidNumber = csid[1] + 64;
	}
	else if (len == CChunk::GetByteLength(BASE2))
	{
		csidNumber = (csid[2] * 256) + csid[1] + 64;
	}
	else
		return -1;

	*pCsid = csidNumber;
	
	return 0;
}

int CChunk::GetTimestamp(uint32_t *pTs)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t ts;
	int len = 0;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == TIMESTAMP)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&ts,&len);
	*pTs = ::BigToHost24(&ts);
	return 0;
}

int CChunk::GetTimestampDelta(uint32_t *pTsDelta)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t tsDelta; 
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == TIMESTAMP_DELTA)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&tsDelta, &len);
	*pTsDelta = ::BigToHost24(&tsDelta);
	return 0;
}

int CChunk::GetMessageLength(uint32_t *pMsgLen)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t msgLen;
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == MESSAGE_LENGTH)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&msgLen, &len);
	*pMsgLen = ::BigToHost24(&msgLen);
	return 0;
}

int CChunk::GetMessageTypeID(uint8_t *pMsgTypeID)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint8_t msgTypeID;
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == MESSAGE_TYPE_ID)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&msgTypeID, &len);
	*pMsgTypeID = msgTypeID;
	return 0;
}

int CChunk::GetMessageStreamID(uint32_t *pMsgStreamID)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t msgStreamID; 
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == MESSAGE_STREAM_ID)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	field->Copy(&msgStreamID, &len);
	*pMsgStreamID = ::BigToHost32(&msgStreamID);
	return;
}

int CChunk::GetExtendedTimestamp(uint32_t *pExTs)
{
	const bool complete = (m_BasicHeader != BasicHeaderType::INVALID && m_MsgHeader != MessageHeaderType::INVALID && m_ExT != ExtendedTimestampType::INVALID);
	auto it = m_Fields.begin();
	ChunkHeaderField *field = NULL;
	uint32_t exTs; 
	int len;

	if (!complete)
		return -1;
	for (it = m_Fields.begin(); it != m_Fields.end(); it++)
	{
		if ((*it)->m_Type == EXTENDED_TIMESTAMP)
		{
			field = *it;
			break;
		}
	}

	if (field == NULL)
		return -1;

	if (m_ExT == EXT0)
	{
		*pExTs = 0;
		return 0; 
	}
	else
	{
		field->Copy(&exTs, &len);
		*pExTs = ::BigToHost32(&exTs);
		return 0;
	}


}