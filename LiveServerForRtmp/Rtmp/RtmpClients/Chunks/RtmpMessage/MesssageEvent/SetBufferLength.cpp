#include "SetBufferLength.h"

CSetBufferLength::CSetBufferLength()
{

}

CSetBufferLength::~CSetBufferLength()
{

}

CSetBufferLength::Object* CSetBufferLength::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);
	obj->streamID = ::BigToHost32(num);

	memcpy(num, payload.buf + 2 + 4, 4);
	obj->bufferLength = ::BigToHost32(num);

	return obj;
}

void CSetBufferLength::FreeObject(CSetBufferLength::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}