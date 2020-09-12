#pragma once
#include "RtmpMessage/AbortMessage.h"
#include "RtmpMessage/Acknowledgement.h"
#include "RtmpMessage/AggregateMessage.h"
#include "RtmpMessage/AudioMessage.h"
#include "RtmpMessage/CommandMessage.h"
#include "RtmpMessage/DataMessage.h"
#include "RtmpMessage/SetChunkSize.h"
#include "RtmpMessage/SetPeerBandwidth.h"
#include "RtmpMessage/SharedObjectMessage.h"
#include "RtmpMessage/UserControlMessages.h"
#include "RtmpMessage/VideoMessage.h"
#include "RtmpMessage/WindowAcknowledgementSize.h"

#include "Send/SendChunk.h"

class CHandleMessage :public CSendChunk,
					public CAbortMessage,\
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
	CHandleMessage();
	virtual ~CHandleMessage();

protected:
	int HandleMessage(CBaseMessage* pMsg);
	
private:
	//处理RTMP协议的消息
	int AcknowledgementHandle(uint32_t sequenceNumber);
	int AggregateMessageHandle(uint32_t sequenceNumber);
	int AudioMessageHandle();
	int CommandMessageHandle(CommandEnum cType, void *pCls);
	int DataMessageHandle();
	int SetPeerBandwidthHandle();
	int SharedObjectMessageHandle();
	int UserControlMessagesHandle();
	int VideoMessageHandle();
	int WindowAcknowledgementSizeHandle(uint32_t winAckSize);

	//CommandMessageHandle 的children
	int CMConnectHandle(CCommandConnect *pCmd);
	int CMCallHandle();
	int CMCloseHandle();
	int CMCloseStreamHandle();
	int CMCreateStreamHandle();
	int CMPlayHandle();
	int CMPlay2Handle();
	int CMDeleteStreamHandle();
	int CMReceiveAudioHandle();
	int CMReceiveVideoHandle();
	int CMReceivePublishHandle();
	int CMSeekHandle();
	int CMPauseHandle();
};