#include "PingResponse.h"

CPingResponse::CPingResponse()
{

}

CPingResponse::~CPingResponse()
{

}

CPingResponse::Object CPingResponse::Decode(CBaseMessage* pMsg)
{
	Object obj = { 0 };
	CBaseMessage::Payload payload = pMsg->GetPayload();
	uint8_t num[4] = { 0 };

	memcpy(num, payload.buf + 2, 4);

	obj.timestamp = ::BigToHost32(num);
	return obj;
}