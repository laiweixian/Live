#include "AbortMessage.h"

CAbortMessage::CAbortMessage()
{

}

CAbortMessage::~CAbortMessage()
{

}

int CAbortMessage::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t csid = 0;
	CBaseMessage::Payload* payload = pMsg->GetPayload();

	memcpy(buf,payload->buf,payload->bufSize);
	csid = BigToHost32(buf);
	return AbortMessageHandle(csid);
}