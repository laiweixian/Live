#include "UserControlMessages.h"

CUserControlMessages::CUserControlMessages(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{
	m_Content.eType = EventType::NONE;
	m_Content.eData = {0};
}

CUserControlMessages::~CUserControlMessages()
{

}

CBaseMessage::MessageType CUserControlMessages::GetType()
{
	return CBaseMessage::MessageType::USER_CONTROL_MESSAGES;
}

CUserControlMessages::Content CUserControlMessages::GetContent()
{
	CUserControlMessages::Content event;
	uint16_t eType;
	uint32_t streamID = 0, bufferLength = 0, ts = 0;

	memcpy(&eType, m_Payload.buff, 2);
	eType = ::BigToHost16(&eType);
	switch (eType)
	{
	case EventType::NONE:
		event.eType = EventType::NONE;
		break;

	case EventType::STREAM_BEGIN:
		event.eType = EventType::STREAM_BEGIN;
		memcpy(&streamID, m_Payload.buff + 2, 4);
		streamID = ::BigToHost32(&streamID);
		event.eData.data_stream_begin = streamID;
		break;

	case EventType::STREAM_EOF:
		event.eType = EventType::STREAM_EOF;
		memcpy(&streamID, m_Payload.buff + 2, 4);
		streamID = ::BigToHost32(&streamID);
		event.eData.data_stream_eof = streamID;
		break;

	case EventType::STREAM_DRY:
		event.eType = EventType::STREAM_DRY;
		memcpy(&streamID, m_Payload.buff + 2, 4);
		streamID = ::BigToHost32(&streamID);
		event.eData.data_stream_dry = streamID;
		break;

	case EventType::SET_BUFFER_LENGTH:
		event.eType = EventType::SET_BUFFER_LENGTH;
		memcpy(&streamID, m_Payload.buff + 2, 4);
		streamID = ::BigToHost32(&streamID);
		memcpy(&bufferLength, m_Payload.buff + 2 + 4, 4);
		bufferLength = ::BigToHost32(&bufferLength);

		event.eData.data_set_buffer_length.streamid = streamID;
		event.eData.data_set_buffer_length.buffer_length = bufferLength;
		break;

	case EventType::STREAM_IS_RECORDED:
		event.eType = EventType::STREAM_IS_RECORDED;
		memcpy(&streamID, m_Payload.buff + 2, 4);
		streamID = ::BigToHost32(&streamID);
		event.eData.data_stream_is_recorded = streamID;
		break;

	case EventType::PING_REQUEST:
		event.eType = EventType::PING_REQUEST;
		memcpy(&ts, m_Payload.buff + 2, 4);
		ts = ::BigToHost32(&ts);
		event.eData.data_ping_request = ts;
		break;
	case EventType::PING_RESPONSE:
		event.eType = EventType::PING_RESPONSE;
		memcpy(&ts, m_Payload.buff + 2, 4);
		ts = ::BigToHost32(&ts);
		event.eData.data_ping_response = ts;
		break;
	default:
	
		break;
	}

	m_Content = event;
	return m_Content;
}

