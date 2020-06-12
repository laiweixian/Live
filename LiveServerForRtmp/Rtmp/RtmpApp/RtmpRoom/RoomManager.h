#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"

#define	ROOMS_OK		0
#define ROOMS_FAILURE	1
#define ERR_ROOM_NO_EXIST -1

class CRtmpRoomManager
{
public:
	CRtmpRoomManager();
	~CRtmpRoomManager();


	CRtmpRoom*	SearchRoom(CPlayer  *pPlayer);
	CRtmpRoom*  SearchRoom(CPublisher *pPublisher);

private:
	vector<CRtmpRoom*> m_Rooms;
};