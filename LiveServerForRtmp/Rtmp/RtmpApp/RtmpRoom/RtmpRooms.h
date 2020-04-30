#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"

class IRtmpRoomsEvent
{
protected:
	IRtmpRoomsEvent() = default;
	IRtmpRoomsEvent() = default;
public:
	virtual void On
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