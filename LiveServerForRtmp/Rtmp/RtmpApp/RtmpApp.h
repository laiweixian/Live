#pragma once

#include "../RtmpModule.h"
#include "RtmpRoom/RtmpRoom.h"

class CRtmpApp : public CRtmpModule
{
public:
	CRtmpApp();
	~CRtmpApp();

private:
	vector<CRtmpRoom*> m_Rooms;
	CRtmpRoom *m_TempRoom;
};
