#include "HandleAbortMessage.h"

CHandleAbortMessage::CHandleAbortMessage()
{

}

CHandleAbortMessage::~CHandleAbortMessage()
{

}

int CHandleAbortMessage::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t csid = 0;

	memcpy(buf,pMsg->GetData(),4);
	csid = BigToHost32(buf);
	return SetAbortMessage(csid);
}