#pragma once

#include "../RtmpMessage/CommandMessage.h"
#include "../RtmpMessage/SetChunkSize.h"
#include "../RtmpMessage/UserControlMessages.h"


//Process ,when createStream done
//1.(Receive) Command Message (play)
//2.(Send) SetChunkSize		
//3.(Send) UserControl (StreamIsRecorded)
//4.(Send) UserControl (StreamBegin)
//5.(Send) Command Message (onStatus-play reset)
//6.(Send) Command Message (onStatus-play start)
//7.(Send) Audio Message & Video Message

class CPlayMission
{
public:
	struct Object {};

protected:
	CPlayMission();
	virtual ~CPlayMission();

protected:
	void Active();
	void InActive();
	int Continue();
	bool Complete();

	virtual int Send2MySelf(CBaseMessage* pMsg) = 0;

};
