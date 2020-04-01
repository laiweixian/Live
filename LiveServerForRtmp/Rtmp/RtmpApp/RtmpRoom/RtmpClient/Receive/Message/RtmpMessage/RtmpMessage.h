#pragma once

#include "AbortMessage.h"
#include "Acknowledgement.h"
#include "AudioMessage.h"
#include "AggregateMessage.h"
#include "CommandMessage.h"
#include "DataMessage.h"
#include "SetChunkSize.h"
#include "SetPeerBandwidth.h"
#include "SharedObjectMessage.h"
#include "UserControlMessages.h"
#include "VideoMessage.h"
#include "WindowAcknowledgementSize.h"

class CRtmpMessage
{
public:
	CRtmpMessage();
	~CRtmpMessage();

	static CBaseMessage* CreateMessage(uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId);


};