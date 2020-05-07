#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"

class IRtmpRoomsEvent
{
protected:
	IRtmpRoomsEvent() = default;
	IRtmpRoomsEvent() = default;
public:
};


class CRtmpRooms
{
public:
	CRtmpRooms();
	~CRtmpRooms();

	

private:
	vector<CRtmpRoom*> m_Rooms;
	CRtmpRoom*		   m_TempRoom;
};