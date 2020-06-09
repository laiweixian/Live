#include "Player.h"
#include "../RtmpRooms.h"


CPlayer::CPlayer() : m_Name(""),m_Room(NULL)
{

}

CPlayer::~CPlayer()
{

}

int CPlayer::Run(string name)
{
	CRtmpRooms *pInstance = NULL;
	CRtmpRoom  *pRoom = NULL;

	if (m_Room != NULL)
		return 0;

	pInstance = CRtmpRooms::GetInstance();
	pRoom = pInstance->SearchRoom(this);
	if (pRoom == NULL)
		return -1;

	m_Room = pRoom;
	m_Room->Join(this);
	return 0;
}

int CPlayer::Pause()
{
	if (m_Room == NULL)	return -1;
}

int CPlayer::Stop()
{
	if (m_Room == NULL)	return -1;

	m_Room->Leave(this);
	m_Room = NULL;
}

int CPlayer::ConnectRoom(string name)
{
	return Run(name);
}

int CPlayer::DisConnectRoom()
{
	return Stop();
}

bool CPlayer::GetActive()
{
	return (m_Room != NULL);
}

string CPlayer::GetName()
{
	return m_Name;
}