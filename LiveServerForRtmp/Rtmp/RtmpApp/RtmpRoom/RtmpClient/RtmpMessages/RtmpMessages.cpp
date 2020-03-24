#include "RtmpMessages.h"

CRtmpMessages::CRtmpMessages() :m_ChunkSize(DEFAULT_CHUNK_SIZE), \
m_WindowAcknowledgementSize(0), \
m_ReceiveByteLength(0)
{

}

CRtmpMessages::~CRtmpMessages()
{

}

int CRtmpMessages::OnReceive(char *buff, const int buffLen)
{
	return DeMultiplexing(buff, buffLen);
}

int CRtmpMessages::DeMultiplexing(char *buff, const int buffLen)
{
	int ret;

}

CChunk*  CRtmpMessages::DeMultiplexingChunkHeader(char *buff, const int buffLen, int* outHeaderLen)
{
	int headerLen = 0;
	CChunk *pChunkHeader = NULL;

	if (buff == NULL || buffLen <= 0)
		return NULL;

	pChunkHeader = CChunk::DeMultiplexing(buff, buffLen, &headerLen);
	if (pChunkHeader == NULL)
		return 0;

	*outHeaderLen = headerLen;
	return pChunkHeader;
}


int CRtmpMessages::DeMultiplexingChunkData(CChunk* pChunk, char *buff, const int buffLen)
{
	const MessageHeaderType msgType = pChunk->GetMessageHeaderType();
	ChunkHeaderInfo info = pChunk->GetInfo();
	ChunkHeaderInfo prevInfo;
	int chunkDataLen = 0;
	CRtmpMsg *pMsg = NULL, *preMsg = NULL;
	int remainLength = 0;

	switch (msgType)
	{
	case MessageHeaderType::INVALID:

		break;
	case MessageHeaderType::MSG0:
		pMsg = new CRtmpMsg(info.timestamp, info.message_length, info.message_type_id, info.message_stream_id, info.csid);
		break;
	case MessageHeaderType::MSG1:
		prevInfo = m_ChunkInfos.at(m_ChunkInfos.size() - 1);

		info.timestamp = prevInfo.timestamp + info.timestamp_delta;
		info.message_stream_id = prevInfo.message_stream_id;
		pMsg = new CRtmpMsg(info.timestamp, info.message_length, info.message_type_id, info.message_stream_id, info.csid);

		break;
	case MessageHeaderType::MSG2:
		prevInfo = m_ChunkInfos.at(m_ChunkInfos.size() - 1);

		info.timestamp = prevInfo.timestamp + info.timestamp_delta;
		info.message_length = prevInfo.message_length;
		info.message_type_id = prevInfo.message_type_id;
		info.message_stream_id = prevInfo.message_stream_id;
		pMsg = new CRtmpMsg(info.timestamp, info.message_length, info.message_type_id, info.message_stream_id, info.csid);

		break;
	case MessageHeaderType::MSG3:
		info = prevInfo;
		info.timestamp += info.timestamp_delta;
		preMsg = m_Msgs.at(m_Msgs.size() - 1);
		if (preMsg->IsEnd())
		{
			pMsg = new CRtmpMsg(info.timestamp, info.message_length, info.message_type_id, info.message_stream_id, info.csid);
		}
		else
		{
			pMsg = preMsg;
		}
		break;
	default:
		break;
	}

	if (pMsg != preMsg)
	{
		m_Msgs.push_back(pMsg);
		m_ChunkInfos.clear();
	}
	m_ChunkInfos.push_back(info);


	remainLength = pMsg->GetMessageLength() - pMsg->GetPayloadLength();
	remainLength = remainLength > m_ChunkSize ? m_ChunkSize : remainLength;
	pMsg->Append(buff, remainLength);

	return remainLength;
}

int CRtmpMessages::HandMessage(CRtmpMsg *pMsg)
{
	const uint8_t *ptr = pMsg->GetPtr();
	const uint32_t length = pMsg->GetPtrLength();

	//最复杂的处理
	switch (pMsg->GetMessageTypeID())
	{
		//protocol control message
	case 1:	SetChunkSize(ptr, length);				break;
	case 2: AbortMessage(ptr, length);				break;
	case 3: Acknowledgement(ptr, length);			break;
	case 5:	WindowAcknowledgementSize(ptr, length);	break;
	case 6:	SetPeerBandwidth(ptr, length);			break;

		//user control messages
	case 4: UserControlMessages(ptr, length);		break;
	case 20: CommandMessage(20, ptr, length);			break;
	case 17: CommandMessage(17, ptr, length);			break;
	case 18: DataMessage(18, ptr, length);			break;
	case 15: DataMessage(15, ptr, length);			break;
	case 19: SharedObjectdMessage(19, ptr, length);	break;
	case 16: SharedObjectdMessage(16, ptr, length);	break;
	case 8: AudioMessage(ptr, length);				break;
	case 9: VideoMessage(ptr, length);				break;
	case 22: AggregateMessage(ptr, length);			break;
	default:
		break;
	}
}


int CRtmpMessages::SetChunkSize(const uint8_t* buff, const int buffLen)
{
	const int byteLength = 4;
	uint32_t chunkSize = 0;

	if (buffLen != byteLength)
		return INVALID_RTMP_MESSAGE;

	memcpy(&chunkSize, buff, buffLen);
	chunkSize = ::BigToHost32(&chunkSize);

	m_ChunkSize = chunkSize;
	return SAR_OK;
}

int CRtmpMessages::AbortMessage(const uint8_t* buff, const int buffLen)
{
	const int byteLength = 4;
	uint32_t chunkStreamID;
	CRtmpMsg *prevMsg = NULL;
	const int msgCount = m_Msgs.size();
	auto it = m_Msgs.end();

	if (buffLen != byteLength)
		return INVALID_RTMP_MESSAGE;

	if (msgCount < 2)
		return INVALID_RTMP_MESSAGE;

	prevMsg = *((it--)--);
	memcpy(&chunkStreamID, buff, buffLen);
	chunkStreamID = ::BigToHost32(&chunkStreamID);

	if (prevMsg->GetCSID() != chunkStreamID)
		return INVALID_RTMP_MESSAGE;

	m_Msgs.erase(it);
	delete prevMsg;

	return SAR_OK;
}

int CRtmpMessages::Acknowledgement(const uint8_t* buff, const int buffLen)
{
	//待定
	const int byteLength = 4;
	uint32_t sequenceNumber = 0;

	if (buffLen != byteLength)
		return INVALID_RTMP_MESSAGE;

	memcpy(&sequenceNumber, buff, buffLen);
	sequenceNumber = ::BigToHost32(&sequenceNumber);

}

int CRtmpMessages::WindowAcknowledgementSize(const uint8_t* buff, const int buffLen)
{
	const int byteLength = 4;
	uint32_t winAckSize = 0;

	if (buffLen != byteLength)
		return INVALID_RTMP_MESSAGE;

	memcpy(&winAckSize, buff, buffLen);
	winAckSize = ::BigToHost32(&winAckSize);

	m_WindowAcknowledgementSize = winAckSize;
	return SAR_OK;
}

int CRtmpMessages::SetPeerBandwidth(const uint8_t* buff, const int buffLen)
{
	//待定
	const int byteLength = 5;
	uint32_t winAckSize;
	uint8_t limitType;
	int offset = 0;

	if (buffLen != byteLength)
		return INVALID_RTMP_MESSAGE;

	memcpy(&winAckSize, buff, 4);			offset += 4;
	memcpy(&limitType, buff + offset, 1);	offset += 1;

}

int CRtmpMessages::UserControlMessages(const uint8_t* buff, const int buffLen)
{
	//待定
	const int headerLength = 10;
	const uint16_t StreamBegin = 0, StreamEOF = 1, StreamDry = 2, \
		SetBufferLength = 3, StreamIsRecorded = 4, PingRequest = 6, PingResponse = 7;
	uint32_t payloadLength = 0;
	uint16_t eventType = 0;
	int offset = 0;


	if (buffLen < headerLength)
		return INVALID_RTMP_MESSAGE;

	memcpy(&payloadLength, buff + 1, 3);
	payloadLength = ::BigToHost32(&payloadLength);

	if (buffLen != headerLength + payloadLength)
		return INVALID_RTMP_MESSAGE;

	offset += headerLength;

	memcpy(&eventType, buff, 2);
	eventType = ::BigToHost16(&eventType);
	offset += 2;

	switch (eventType)
	{
	case StreamBegin:
		return INVALID_RTMP_MESSAGE; //only send ,no receive
		break;
	case StreamEOF:
		return INVALID_RTMP_MESSAGE; //only send ,no receive
		break;
	case StreamDry:
		return INVALID_RTMP_MESSAGE; //only send ,no receive
		break;
	case SetBufferLength:
		break;
	case StreamIsRecorded:
		return INVALID_RTMP_MESSAGE; //only send ,no receive
		break;
	case PingRequest:
		return INVALID_RTMP_MESSAGE; //only send ,no receive
		break;
	case PingResponse:
		break;
	default:
		break;
	}


}


int CRtmpMessages::CommandMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen)
{
	CAMF0 *amf0 = NULL;
	CAMF3 *amf3 = NULL;

	if (msgTypeId == 20)
	{
		//AMF0
		amf0 = CAMF0::CreateAMF0(const_cast<UINT8*>(buff),buffLen);
		if (amf0 == NULL)
			return INVALID_RTMP_MESSAGE;

		//connect,createStream,publish,play,pause
		//onstatus,result
		//command name,transaction ID,command object

	}
	else if (msgTypeId == 17)
	{
		//AMF3
	}
}

int CRtmpMessages::DataMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen)
{

}

int CRtmpMessages::SharedObjectdMessage(const uint8_t msgTypeId, const uint8_t* buff, const int buffLen)
{

}

int CRtmpMessages::AudioMessage(const uint8_t* buff, const int buffLen)
{

}

int CRtmpMessages::VideoMessage(const uint8_t* buff, const int buffLen)
{

}

int CRtmpMessages::AggregateMessage(const uint8_t* buff, const int buffLen)
{

}