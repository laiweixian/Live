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



class CReceiveMessage
{
protected:
	CReceiveMessage();
	virtual ~CReceiveMessage();
protected:
	//����RTMPЭ�����Ϣ
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

	//CommandMessageHandle ��children
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

private:
};