#include "StreamBegin.h"

CStreamBegin::CStreamBegin()
{

}

CStreamBegin::~CStreamBegin()
{

}

CStreamBegin::Object* CStreamBegin::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = {0};

	memcpy(num, payload.buf+2,4);

	obj->streamID = ::BigToHost32(num);
	return obj;
}

void CStreamBegin::FreeObject(CStreamBegin::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}

