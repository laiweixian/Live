#include "RtmpClient/Player.h"
#include "RtmpClient/Publisher.h"
#include "RtmpRoom.h"

CRtmpRoom::CRtmpRoom(string name) : m_Name(name),m_Publish(NULL)
{
	
}

CRtmpRoom::~CRtmpRoom()
{

}

int CRtmpRoom::SetOwner(CPublish* pPublish)
{
	if (!m_Publish)
		m_Publish = pPublish;
}

int CRtmpRoom::BroadcastAudio(CPublish* pPublish,const char* src, const int srcLen)
{

}

int CRtmpRoom::BroadcastVideo(CPublish* pPublish,const char* src, const int srcLen)
{

}

int CRtmpRoom::BroadcastMsg(CPublish* pPublish,const char* src, const int srcLen)
{

}

int CRtmpRoom::DisbandRoom(CPublish* pPublish)
{

}

int CRtmpRoom::Enter(CPlayer* pPlayer)
{

}

int CRtmpRoom::Leave(CPlayer* pPlayer)
{

}

string CRtmpRoom::GetName()
{
	return m_Name;
}

int CRtmpRoom::GetCount()
{
	return m_Players.size();
}

CPlayer* CRtmpRoom::GetPlayer(int index)
{
	const int count = m_Players.size();
	if (count == 0)
		return NULL;
	return m_Players.at(index);
}