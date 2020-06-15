#include "Player.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpRoom.h"


CPlayer::CPlayer() : m_Name(""),m_Room(NULL)
{

}

CPlayer::~CPlayer()
{

}

bool CPlayer::GetActive()
{
	return (m_Room != NULL);
}

string CPlayer::GetName()
{
	return m_Name;
}