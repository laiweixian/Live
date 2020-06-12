#pragma once

#include "BaseMessage.h"

#define DECLARE_USER_CONTROL_MESSAGES													\
	enum EventType{NONE = 0xff,STREAM_BEGIN = (uint16_t(0)),							\
				   STREAM_EOF = (uint16_t(1)),STREAM_DRY = (uint16_t(2)),				\
				   SET_BUFFER_LENGTH = (uint16_t(3)),STREAM_IS_RECORDED = (uint16_t(4)),\
				   PING_REQUEST = (uint16_t(6)),PING_RESPONSE = (uint16_t(7))};			\
	struct SetBufferLength{uint32_t streamid;uint32_t buffer_length;};					\
	union EventData{uint32_t data_stream_begin;uint32_t data_stream_eof;				\
					uint32_t data_stream_dry;SetBufferLength data_set_buffer_length;	\
					uint32_t data_stream_is_recorded;uint32_t data_ping_request;		\
					uint32_t data_ping_response;};										\
	struct Content{EventType eType;EventData eData;};									\
	
/*-----------------------------------------------------------------------------------------*/
class CUserControlMessages : public CBaseMessage
{
public:
	DECLARE_USER_CONTROL_MESSAGES
	CUserControlMessages(uint32_t csid,uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CUserControlMessages();
	
	//CBaseMessage
	CBaseMessage::MessageType GetType();

	//property
	CUserControlMessages::Content GetContent();

private:
	CUserControlMessages::Content m_Content;
};