#include "RtmpRooms.h"

CRtmpRooms* CRtmpRooms::m_Instance = NULL;

CRtmpRooms::CRtmpRooms() 
{

}

CRtmpRooms::~CRtmpRooms()
{

}

CRtmpRooms* CRtmpRooms::GetInstance()
{
	if (m_Instance == NULL)
		m_Instance = new CRtmpRooms;
	return m_Instance;
}

void CRtmpRooms::Destroy()
{
	delete this;
}

bool CRtmpRooms::SearchRoom(string name)
{
	auto it = m_Rooms.begin();
	CRtmpRoom *pRoom = NULL;

	for (it = m_Rooms.begin(); it != m_Rooms.end(); it++)
	{
		pRoom = *it;
		if (name.compare(pRoom->GetName()) == 0)
			goto success;
	}

	return false;
success:
	return true;
}

CRtmpRoom* CRtmpRooms::GetRoom(string name) const
{
	auto it = m_Rooms.begin();
	CRtmpRoom *pRoom = NULL;

	for (it = m_Rooms.begin(); it != m_Rooms.end(); it++)
	{
		pRoom = *it;
		if (name.compare(pRoom->GetName()) == 0)
			goto success;
	}

	return NULL;
success:
	return pRoom;
}