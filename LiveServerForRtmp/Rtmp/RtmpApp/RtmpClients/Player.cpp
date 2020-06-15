#include "Player.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpRoom.h"


CPlayer::CPlayer() : m_Name(""),m_Room(NULL)
{

}

CPlayer::~CPlayer()
{

}

int CPlayer::PlayVideo(CVideoMessage *pMsg)
{
	return 0;
}

int CPlayer::PlayAudio(CAudioMessage *pMsg)
{
	return 0;
}

int CPlayer::PlayMsg(CBaseMessage *pMsg)
{
	return 0;
}

int CPlayer::Connenct(string name)
{
	return 0;
}

int CPlayer::DisConnect()
{
	return 0;
}

