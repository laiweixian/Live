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

	struct Object { char url[1024]; };

protected:
	
	void SetReceiveCommandConnect(CCommandConnect::Object *pObj);
	void SetReceiveWinAckSize(CWindowAcknowledgementSize::Object *pObj);

	void Active();
	void InActive();
	int Continue();
	bool Complete();
	virtual int SendMessage(CBaseMessage* pMsg) = 0;
protected:


};
