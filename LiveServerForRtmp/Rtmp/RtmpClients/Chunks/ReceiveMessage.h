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

#include "Mission/ConnectMission.h"
#include "Mission/PlayMission.h"
#include "Mission/PublishMission.h"
#include "Mission/CreateStreamMission.h"


class CReceiveMessage : public CConnectMission,\
						public CCreateStreamMission,
						public CPlayMission,\
						public CPublishMission
{
protected:
	CReceiveMessage();
	virtual ~CReceiveMessage();
protected:
	//处理RTMP协议的消息
	int HandleMessage(CBaseMessage* pMsg);
private:
	int AcknowledgementHandle(CAcknowledgement::Object *pObj);
	int AggregateMessageHandle(CAggregateMessage::Object *pObj);
	int AudioMessageHandle();
	int CommandMessageHandle(CCommandMessage::Object *pObj);
	virtual int AbortMessageHandle(CAbortMessage::Object *pObj) = 0;
	virtual int SetChunkSizeHandle(CSetChunkSize::Object *pObj) = 0;
	int DataMessageHandle();
	int SetPeerBandwidthHandle(CSetPeerBandwidth::Object *pObj);
	int SharedObjectMessageHandle();
	int UserControlMessagesHandle();
	int VideoMessageHandle();
	int WindowAcknowledgementSizeHandle(CWindowAcknowledgementSize::Object  *pObj);

	//CommandMessageHandle 的children
	int CMConnectHandle(CCommandConnect::Object *pObj);
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

private:


};