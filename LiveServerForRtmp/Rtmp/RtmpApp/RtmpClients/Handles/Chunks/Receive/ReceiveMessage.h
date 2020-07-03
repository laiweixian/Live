#pragma once
#include "MessageHandle/HandleAbortMessage.h"
#include "MessageHandle/HandleAcknowledgement.h"
#include "MessageHandle/HandleAggregateMessage.h"
#include "MessageHandle/HandleAudioMessage.h"
#include "MessageHandle/HandleCommandMessage.h"
#include "MessageHandle/HandleDataMessage.h"
#include "MessageHandle/HandleSetChunkSize.h"
#include "MessageHandle/HandleSetPeerBandwidth.h"
#include "MessageHandle/HandleSharedObjectMessage.h"
#include "MessageHandle/HandleUserControlMessages.h"
#include "MessageHandle/HandleVideoMessage.h"
#include "MessageHandle/HandleWindowAcknowledgementSize.h"

class CReceiveMessage :public CHandleAbortMessage,\
					public CHandleAcknowledgement,\
					public CHandleAggregateMessage,\
					public CHandleAudioMessage,\
					public CHandleCommandMessage,\
					public CHandleDataMessage,\
					public CHandleSetChunkSize,\
					public CHandleSetPeerBandwidth,\
					public CHandleSharedObjectMessage,\
					public CHandleUserControlMessages,\
					public CHandleVideoMessage,\
					public CHandleWindowAcknowledgementSize
{
protected:
	CReceiveMessage();
	virtual ~CReceiveMessage() ;

protected:
	int HandleMessage(CBaseMessage* pMsg);
};