#pragma once
#include "Message/AbortMessage.h"
#include "Message/Acknowledgement.h"
#include "Message/AggregateMessage.h"
#include "Message/AudioMessage.h"
#include "Message/CommandMessage.h"
#include "Message/DataMessage.h"
#include "Message/SetChunkSize.h"
#include "Message/SetPeerBandwidth.h"
#include "Message/SharedObjectMessage.h"
#include "Message/UserControlMessages.h"
#include "Message/VideoMessage.h"
#include "Message/WindowAcknowledgementSize.h"

class CReceiveMessage :public CAbortMessage,\
					public CAcknowledgement,\
					public CAggregateMessage,\
					public CAudioMessage,\
					public CCommandMessage,\
					public CDataMessage,\
					public CSetChunkSize,\
					public CSetPeerBandwidth,\
					public CSharedObjectMessage,\
					public CUserControlMessages,\
					public CVideoMessage,\
					public CWindowAcknowledgementSize
{
protected:
	CReceiveMessage();
	virtual ~CReceiveMessage() ;

protected:
	int HandleMessage(CBaseMessage* pMsg);
};