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

class CHandleMessage :public CAbortMessage,\
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
	//����RTMPЭ�����Ϣ
	int AcknowledgementHandle(uint32_t sequenceNumber);
	int AggregateMessageHandle(uint32_t sequenceNumber);
	int AudioMessageHandle();
	int CommandMessageHandle(CommandMessageObject *pObj);
	int DataMessageHandle();
	int SetPeerBandwidthHandle();
	int SharedObjectMessageHandle();
	int UserControlMessagesHandle();
	int VideoMessageHandle();
	int WindowAcknowledgementSizeHandle(uint32_t winAckSize);

	int CMConnectHandle(ConnectObject* pObj);
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