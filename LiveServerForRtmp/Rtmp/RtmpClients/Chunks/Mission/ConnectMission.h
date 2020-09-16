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

	enum SendStep {NONE,WIN_ACK_SIZE,SET_PEER_BANDWIDTH,USER_CONTROL_MESSAGE,CONNECT_RESPONSE};
	struct Object { char rtmpUrl[1024]; };
	


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
	
	Object m_Obj;
};
