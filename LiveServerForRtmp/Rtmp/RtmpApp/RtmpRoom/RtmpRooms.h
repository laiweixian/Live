#pragma once

#include "stdafx.h"
#include "RtmpRoom.h"

class CPlayer;
class CPublish;

class CRtmpRooms
{
private:
	CRtmpRooms();
	~CRtmpRooms();
public:
	static CRtmpRooms* GetInstance();
	void Destroy();

	bool SearchRoom(string name);
	CRtmpRoom* GetRoom(string name) const;

	int CreateRoom(string name);
	int DestroyRoom(string name);



public:
	static CRtmpRooms* m_Instance;
protected:
	vector<CRtmpRoom*> m_Rooms;
};