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

CRtmpRoom* CRtmpRooms::EnterRoom(string name,CPlayer* pPlayer)
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

CRtmpRoom* CRtmpRooms::CreateRoom(string name,CPublish* pPublish)
{
	auto it = m_Rooms.begin();
	CRtmpRoom *pRoom = NULL;

	for (it = m_Rooms.begin(); it != m_Rooms.end(); it++)
	{
		pRoom = *it;
		if (name.compare(pRoom->GetName()) == 0)
			goto exist;
	}

	pRoom = new CRtmpRoom(name);

	
exist:
	return NULL;
}