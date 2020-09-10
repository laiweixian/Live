#pragma once
#include "AbortMessage.h"
#include "Acknowledgement.h"
#include "AggregateMessage.h"
#include "AudioMessage.h"
#include "CommandMessage.h"
#include "DataMessage.h"
#include "SetChunkSize.h"
#include "SetPeerBandwidth.h"
#include "SharedObjectMessage.h"
#include "UserControlMessages.h"
#include "VideoMessage.h"
#include "WindowAcknowledgementSize.h"

class CRtmpMessage :	public CAbortMessage,\
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
	CRtmpMessage();
	virtual ~CRtmpMessage();
};