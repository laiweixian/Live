#include "Player.h"
#include "Publisher.h"
#include "Rtmp/RtmpApp/RtmpRoom/RtmpRoom.h"

CPublisher::CPublisher() : m_Name(""),m_Room(NULL)
{

}

CPublisher::~CPublisher()
{

}

int CPublisher::OnEnter(CPlayer* pPlayer)
{
	return 0;
}
int CPublisher::OnLeave(CPlayer* pPlayer)
{
	return 0;
}

bool CPublisher::GetActive()
{
	return true;
}
string CPublisher::GetName()
{
	return m_Name;
}

