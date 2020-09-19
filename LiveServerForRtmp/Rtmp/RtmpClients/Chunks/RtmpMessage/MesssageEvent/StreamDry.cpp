#include "StreamDry.h"

CStreamDry::CStreamDry()
{

}

CStreamDry::~CStreamDry()
{

}

CStreamDry::Object* CStreamDry::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);

	obj->streamID = ::BigToHost32(num);
	return obj;
}

void CStreamDry::FreeObject(CStreamDry::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}