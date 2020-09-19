#pragma once

#include "../RtmpMessage/CommandMessage.h"
#include "../RtmpMessage/WindowAcknowledgementSize.h"
#include "../RtmpMessage/SetPeerBandwidth.h"
#include "../RtmpMessage/UserControlMessages.h"

//Process
//0.(Receive) Command Message(connect)
//1.(Send)Window Acknowledgement Size
//2.(Send)Set Peer Bandwidth
//3.(Receive)Window Acknowledgement Size 
//4.(Send)User Control Message(StreamBegin) 
//5.(Send)Command Message(_result- connect response)



class CConnectMission
{
public:
	CConnectMission();
	~CConnectMission();
	enum SendStat {S_NONE, S_WIN_ACK_SIZE, S_SET_PEER_BANDWIDTH, S_USER_CONTROL_MESSAGE, S_CONNECT_RESPONSE};
	enum ReceiveStat {
		R_NONE, R_COMMAND_CONNENCT, R_WIN_ACK_SIZE
	};
	struct Object { char rtmpUrl[1024]; uint32_t winAckSize; };

protected:
	void SetCommandConnect(CCommandConnect::Object *pObj);
	void SetWinAckSize(CWindowAcknowledgementSize::Object *pObj);

	void Active();
	void InActive();
	int Continue();
	bool Complete();
	virtual int SendMessage(CBaseMessage* pMsg) = 0;

private:
	int SendAckWinSize();
	int SendSetPeerBandwidth();
	int SendUserControlMessage();
	int SendConnectResponse();
protected:
	bool m_Active;
	SendStat m_SStat;
	ReceiveStat m_RStat;
	Object m_Obj;
};
