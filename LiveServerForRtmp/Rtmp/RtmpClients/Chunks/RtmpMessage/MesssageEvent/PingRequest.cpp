#include "PingRequest.h"

CPingRequest::CPingRequest()
{

}

CPingRequest::~CPingRequest()
{

}

CPingRequest::Object* CPingRequest::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);

	obj->timestamp = ::BigToHost32(num);
	return obj;
}

void CPingRequest::FreeObject(CPingRequest::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}

uint8_t* CPingRequest::TranslatePayload(Object obj, uint32_t *outLen)
{
	uint16_t bigEventType = 0;
	uint32_t bigEventData = 0;

	const uint32_t length = 6;
	uint8_t *payload = new uint8_t[length];

	bigEventType = ::HostToBig16(E_T_PING_REQUEST);
	bigEventData = ::HostToBig32(obj.timestamp);

	memcpy(payload,&bigEventType,2);
	memcpy(payload+2,&bigEventData,4);

	*outLen = length;
	return payload;
}

