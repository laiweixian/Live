#include "DataMessage.h"

CDataMessage::CDataMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CDataMessage::~CDataMessage()
{

}

CBaseMessage::MessageType CDataMessage::GetType()
{
	return CBaseMessage::MessageType::DATA_MESSAGE;
}

