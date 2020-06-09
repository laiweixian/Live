#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"

#define	ROOMS_OK		0
#define ROOMS_FAILURE	1
#define ERR_ROOM_NO_EXIST -1

class CRtmpRooms
{
private:
	CRtmpRooms();
	~CRtmpRooms();
public:
	static CRtmpRooms* GetInstance();
	void Destroy();

	CRtmpRoom*	SearchRoom(CPlayer  *pPlayer);
	CRtmpRoom*  SearchRoom(CPublisher *pPublisher);
public:
	static CRtmpRooms* m_Instance;
private:
	vector<CRtmpRoom*> m_Rooms;
};