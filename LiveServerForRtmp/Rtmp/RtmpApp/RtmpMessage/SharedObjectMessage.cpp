#include "SharedObjectMessage.h"

CSharedObjectMessage::CSharedObjectMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CSharedObjectMessage::~CSharedObjectMessage()
{

}

CBaseMessage::MessageType CSharedObjectMessage::GetType()
{
	return CBaseMessage::MessageType::SHARED_OBJECT_MESSAGE;
}

