#include "AbortMessage.h"

CAbortMessage::CAbortMessage()
{

}

CAbortMessage::~CAbortMessage()
{

}

int CAbortMessage::HandleAbortMessage(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t csid = 0;

	memcpy(buf,pMsg->GetData(),4);
	csid = BigToHost32(buf);
	return AbortMessage(csid);
}