#include "UserControlMessages.h"

CUserControlMessages::CUserControlMessages(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, MessageInform inform) :\
CBaseMsg(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CUserControlMessages::~CUserControlMessages()
{

}

RtmpMessageType CUserControlMessages::GetType()
{
	return RtmpMessageType::USER_CONTROL_MESSAGES;
}

void CUserControlMessages::Inform()
{

}