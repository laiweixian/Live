#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"



class CRtmpRooms
{
public:
	CRtmpRooms();
	~CRtmpRooms();

	

private:
	vector<CRtmpRoom*> m_Rooms;
	CRtmpRoom*		   m_TempRoom;
};