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

uint8_t* CSetBufferLength::TranslatePayload(CSetBufferLength::Object obj, uint32_t *outLen)
{
	const uint32_t length = 10;
	uint8_t *payload = new uint8_t[length];
	uint16_t bigEventType = 0;
	uint32_t bigStreamID = 0, bigBufferLength = 0;

	bigEventType = ::HostToBig16(E_T_SET_BUFFER_LENGTH);
	bigStreamID = ::HostToBig32(obj.streamID);
	bigBufferLength = ::HostToBig32(obj.bufferLength);

	memcpy(payload,&bigEventType,2);
	memcpy(payload+2,&bigStreamID,4);
	memcpy(payload+2+4,&bigBufferLength,4);

	*outLen = length;
	return payload;
}