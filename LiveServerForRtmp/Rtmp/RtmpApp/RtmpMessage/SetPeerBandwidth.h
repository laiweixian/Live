#pragma once

#include "BaseMessage.h"

#define DECLARE_SET_PEER_BANDWIDTH \
	struct Content{uint32_t acknowledgementWindowSize;uint8_t limitType;};
	
/*-----------------------------------------------------------------------------------------*/
class CSetPeerBandwidth : public CBaseMessage
{
public:
	DECLARE_SET_PEER_BANDWIDTH

	CSetPeerBandwidth(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);
	~CSetPeerBandwidth();

	//CBaseMessage
	CBaseMessage::MessageType GetType();
	
	//property
	CSetPeerBandwidth::Content GetContent();
private:
	CSetPeerBandwidth::Content m_Content;
};