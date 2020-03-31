#pragma once

#include "stdafx.h"

enum RtmpMessageType
{
	INVALID,
	SET_CHUNK_SIZE, ABORT_MESSAGE, ACKNOWLEDGEMENT, WINDOW_ACKNOWLEDGEMENT_SIZE,
	SET_PEER_BADNWIDTH, USER_CONTROL_MESSAGES, COMMAND_MESSAGE, DATA_MESSAGE,
	SHARED_OBJECT_MESSAGE, AUDIO_MESSAGE, VIDEO_MESSAGE, AGGREGATE_MESSAGE
};

class IMessageInform
{
protected:
	virtual ~IMessageInform() = default;
public:
	IMessageInform() = default;

	virtual void OnMessageInform(RtmpMessageType msgType,void* pObj,const int objSize) = 0;
};

struct MessageHeader
{
	uint32_t timestamp;
	uint32_t messageLength;
	uint8_t messageTypeID;
	uint32_t messageStreamID;
};

struct MessagePayload
{
	char* buff;
	int buffLength;
};

class CBaseMessage
{
public:
	CBaseMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId,IMessageInform* inform);
	virtual ~CBaseMessage();

	//property
	uint32_t GetTimestamp() const ;
	uint32_t GetLength() const;
	uint8_t	 GetTypeID() const;
	uint32_t GetStreamID() const ;

	//ability
	uint32_t GetRemainSize() const;
	int Append(const uint8_t* src, const int srcLen );

	//interface
	virtual RtmpMessageType GetType() = 0;
	virtual void Inform() = 0;

protected:
	IMessageInform* m_Inform;
	MessageHeader  m_Header;
	MessagePayload m_Payload;
	int m_AppendLength;
};