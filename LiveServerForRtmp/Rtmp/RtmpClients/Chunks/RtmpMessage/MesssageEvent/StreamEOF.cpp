#include "StreamEOF.h"

CStreamEOF::CStreamEOF()
{

}

CStreamEOF::~CStreamEOF()
{

}

CStreamEOF::Object* CStreamEOF::Decode(CBaseMessage* pMsg)
{
	Object *obj = new Object ;
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);

	obj->streamID = ::BigToHost32(num);
	return obj;
}

void CStreamEOF::FreeObject(CStreamEOF::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}

uint8_t* CStreamEOF::TranslatePayload(CStreamEOF::Object obj, uint32_t *outLen)
{
	const uint32_t length = 6;
	uint8_t *payload = new uint8_t[length];
	uint16_t bigEventType = 0;
	uint32_t bigStreamID = 0;

	bigEventType = ::HostToBig16(E_T_STREAM_EOF);
	bigStreamID = ::HostToBig32(obj.streamID);

	memcpy(payload,&bigEventType,2);
	memcpy(payload + 2, &bigStreamID, 4);

	*outLen = length;
	return payload;
}

