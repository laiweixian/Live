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