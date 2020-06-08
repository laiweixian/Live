#pragma once

#include "stdafx.h"

#define PUBLISHER_OK	0
#define PUBLISHER_FAILURE 1


class CPlayer;
class CRtmpRoom;

class CPublish
{
protected:
	CPublish();
	virtual ~CPublish();
public:
	virtual void OnEnter(CPlayer* pPlayer) final;
	virtual void OnLeave(CPlayer* pPlayer) final;
	
protected:
	virtual int CreateRoom(string name) final;
	virtual int DestroyRoom() final;

	virtual int BroadcastVideo(const char* src,const int srcLen) final;
	virtual int BroadcastAudio(const char* src, const int srcLen)final;
	virtual int BroadcastMsg(const char* src, const int srcLen)final;

private:
	string m_Name;
	CRtmpRoom *m_Room;
};

