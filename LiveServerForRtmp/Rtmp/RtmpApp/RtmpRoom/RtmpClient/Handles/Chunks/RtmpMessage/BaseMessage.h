#pragma once

#include "stdafx.h"


#define SET_CHUNK_SIZE_TYPE_ID				((uint8_t)1)
#define ABORT_MESSAGE_TYPE_ID				((uint8_t)2)
#define ACKNOWLEDGEMENT_TYPE_ID				((uint8_t)3)
#define WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID	((uint8_t)5)
#define SET_PEER_BADNWIDTH_TYPE_ID			((uint8_t)6)
#define USER_CONTROL_MESSAGES_TYPE_ID		((uint8_t)4)
#define COMMAND_MESSAGE_TYPE_ID_AMF0		((uint8_t)20)
#define COMMAND_MESSAGE_TYPE_ID_AMF3		((uint8_t)17)
#define DATA_MESSAGE_TYPE_ID_AMF0			((uint8_t)18)
#define DATA_MESSAGE_TYPE_ID_AMF3			((uint8_t)15)
#define SHARED_OBJECT_MESSAGE_TYPE_ID_AMF0	((uint8_t)19)
#define SHARED_OBJECT_MESSAGE_TYPE_ID_AMF3	((uint8_t)16)
#define AUDIO_MESSAGE_TYPE_ID				((uint8_t)8)
#define VIDEO_MESSAGE_TYPE_ID				((uint8_t)9)
#define AGGREGATE_MESSAGE_TYPE_ID			((uint8_t)22)

enum RtmpMessageType
{
	INVALID,
	SET_CHUNK_SIZE, ABORT_MESSAGE, ACKNOWLEDGEMENT, WINDOW_ACKNOWLEDGEMENT_SIZE,
	SET_PEER_BADNWIDTH, USER_CONTROL_MESSAGES, COMMAND_MESSAGE, DATA_MESSAGE,
	SHARED_OBJECT_MESSAGE, AUDIO_MESSAGE, VIDEO_MESSAGE, AGGREGATE_MESSAGE
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
	CBaseMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
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
	virtual RtmpMessageType GetType()	 = 0;

protected:
	MessageHeader  m_Header;
	MessagePayload m_Payload;
	int m_AppendLength;
};