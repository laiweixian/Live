#pragma once
#include "../Receive/BaseMessage.h"

#include "MesssageEvent/PingRequest.h"
#include "MesssageEvent/PingResponse.h"
#include "MesssageEvent/SetBufferLength.h"
#include "MesssageEvent/StreamBegin.h"
#include "MesssageEvent/StreamDry.h"
#include "MesssageEvent/StreamEOF.h"
#include "MesssageEvent/StreamIsRecorded.h"


class CUserControlMessages 
{
protected:
	CUserControlMessages();
	 ~CUserControlMessages();
public:
	enum EventType{NONE,STREAM_BEGIN,STREAM_EOF,STREAM_DRY,SET_BUFFER_LENGTH,STREAM_IS_RECORDED,PING_REQUEST,PING_RESPONSE};
	struct Object { EventType  eType; void* eData; };
	static Object* Decode(CBaseMessage* pMsg);
	static CBaseMessage* Encode(uint32_t timestamp, uint32_t msid, Object obj);
	static void FreeObject(Object** ppObj);
};