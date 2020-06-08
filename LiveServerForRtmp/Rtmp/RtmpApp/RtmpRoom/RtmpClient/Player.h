#pragma once
#include "stdafx.h"

#define PLAYER_OK		0
#define PLAYER_FAILURE	1
#define ERR_NO_ROOM		-1


class CRtmpRoom;

class CPlayer
{
protected:
	CPlayer() ;
	virtual ~CPlayer() ;
public:
	virtual int SendVideo(const char* src,const int srcLen) = 0;
	virtual int SendAudio(const char* src, const int srcLen) = 0;
	virtual int SendMsg(const char* src, const int srcLen) = 0;
	
	virtual int OnDisband() = 0;
protected:
	virtual int ConnectRoom(string name) final;
	virtual int DisConnectRoom() final;
protected:
	string m_Name;
	CRtmpRoom *m_Room;
};

