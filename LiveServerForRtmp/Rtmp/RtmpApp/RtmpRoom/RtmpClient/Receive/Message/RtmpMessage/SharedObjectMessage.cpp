#include "SharedObjectMessage.h"

CSharedObjectMessage::CSharedObjectMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId, IMessageInform* inform) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId, inform)
{

}

CSharedObjectMessage::~CSharedObjectMessage()
{

}

RtmpMessageType CSharedObjectMessage::GetType()
{
	return RtmpMessageType::SHARED_OBJECT_MESSAGE;
}

void CSharedObjectMessage::Inform()
{

}