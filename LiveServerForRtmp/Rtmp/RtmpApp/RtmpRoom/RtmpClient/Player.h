#pragma once
#include "stdafx.h"

class CRtmpRoom;


class CPlayer
{
protected:
	CPlayer() ;
	virtual ~CPlayer() ;
public:
	virtual void OnConnect(CRtmpRoom* pRoom) = 0;
	virtual void OnDisConnect() = 0;
	
	virtual int SendVideo(const char* src,const int srcLen) = 0;
	virtual int SendAudio(const char* src, const int srcLen) = 0;
	virtual int SendMsg(const char* src, const int srcLen) = 0;

protected:
	virtual void SetRoom(CRtmpRoom* pRoom) = 0;
	virtual CRtmpRoom* GetRoom() = 0;
};

