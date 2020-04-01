#include "SharedObjectMessage.h"

CSharedObjectMessage::CSharedObjectMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(ts, msgLength, msgTypeId, msgStreamId)
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