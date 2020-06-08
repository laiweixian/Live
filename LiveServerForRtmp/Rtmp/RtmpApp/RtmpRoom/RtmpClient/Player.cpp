#include "Player.h"
#include "../RtmpRooms.h"


CPlayer::CPlayer() : m_Name(""),m_Room(NULL)
{

}

CPlayer::~CPlayer()
{

}

int CPlayer::ConnectRoom(string name)
{
	CRtmpRooms *pInstance = NULL;
	int ret = ROOMS_FAILURE;
	CRtmpRoom *pRoom = NULL;

	if (m_Room)
		goto exist;

	pInstance = CRtmpRooms::GetInstance();

	pRoom = pInstance->SearchRoom(name);
	if (pRoom == NULL)
		goto fail;
	
	m_Room = pRoom;
	m_Room->Enter(this);
	return PLAYER_OK;

fail:
	return ERR_NO_ROOM;
exist:
	return PLAYER_OK;
}

int CPlayer::DisConnectRoom()
{
	if (m_Room == NULL)
		goto fail;

	m_Room->Leave(this);
	return PLAYER_OK;
	
fail:
	return ERR_NO_ROOM;
}