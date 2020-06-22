#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize()
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

int CWindowAcknowledgementSize::HandleWindowAcknowledgementSize(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t winAckSize = 0;

	memcpy(buf,pMsg->GetData(),4);
	winAckSize = BigToHost32(buf);
	return SetWinAckSize(winAckSize);
}