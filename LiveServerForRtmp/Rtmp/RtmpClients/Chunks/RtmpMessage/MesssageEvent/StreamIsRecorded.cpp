#include "StreamIsRecorded.h"

CStreamIsRecorded::CStreamIsRecorded()
{

}

CStreamIsRecorded::~CStreamIsRecorded()
{

}

CStreamIsRecorded::Object* CStreamIsRecorded::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);

	obj->streamID = ::BigToHost32(num);
	return obj;
}

void CStreamIsRecorded::FreeObject(CStreamIsRecorded::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}