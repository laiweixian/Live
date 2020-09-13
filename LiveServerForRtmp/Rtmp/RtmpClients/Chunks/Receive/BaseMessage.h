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

#define DECLARE_BASE_MESSAGE \
	struct Header{uint8_t msgType;uint32_t payloadLength;uint32_t timestamp;uint32_t msid;};\
	struct Payload{uint8_t* buf;uint32_t bufSize;uint8_t *ptr;};
	
class CBaseMessage
{
public:
	DECLARE_BASE_MESSAGE
public:
	CBaseMessage(uint8_t msgType, uint32_t payloadLength, uint32_t timestamp, uint32_t msid, uint8_t* payloadBuf, uint32_t payloadBufLen);
	virtual ~CBaseMessage();
protected:
	CBaseMessage();
public:
	Header GetHeader();
	Payload GetPayload();
	bool Legal();
protected:
	void SetHeader(uint8_t msgType, uint32_t payloadLength, uint32_t timestamp, uint32_t msid);
	void SetPayload(uint8_t* buf, uint32_t bufLength);
	void AppendPayload(uint8_t* buf, uint32_t bufLength);
protected:
	Header m_Header;
	Payload m_Payload;
};
