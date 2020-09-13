#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize()
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

int CWindowAcknowledgementSize::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t winAckSize = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf,payload.bufSize);
	winAckSize = BigToHost32(buf);
	return WindowAcknowledgementSizeHandle(winAckSize);
}