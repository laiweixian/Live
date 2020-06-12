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

CRtmpRoom*	CRtmpRooms::SearchRoom(CPlayer  *pPlayer)
{
	return NULL;
}

CRtmpRoom*  CRtmpRooms::SearchRoom(CPublisher *pPublisher)
{
	return NULL;
}