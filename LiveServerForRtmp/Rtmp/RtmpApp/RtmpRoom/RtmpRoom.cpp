#include "RtmpClient/Player.h"
#include "RtmpClient/Publisher.h"
#include "RtmpRoom.h"



CRtmpRoom::CRtmpRoom(string name) : m_Name(name),m_Publish(NULL)
{
	
}

CRtmpRoom::~CRtmpRoom()
{

}

int CRtmpRoom::Join(CPlayer* pPlayer)
{
	auto it = m_Players.begin();

	for (it = m_Players.begin(); it != m_Players.end(); it++)
	{
		if (pPlayer == *it)
			goto exist;
	}

	m_Players.push_back(pPlayer);


	return 0;
exist:
	return 0;
fail:
	return -1;
}

int CRtmpRoom::Leave(CPlayer* pPlayer)
{
	auto it = m_Players.begin();

	for (it = m_Players.begin(); it != m_Players.end(); it++)
	{
		if (pPlayer == *it)
		{
			m_Players.erase(it);
			goto succeed;
		}	
	}

	return -1;
succeed:
	return 0;
fail:
	return -1;
}

//IRoom4Publisher
int CRtmpRoom::SetOwner(CPublisher *pPublish)
{
	if (m_Publish == NULL)
		m_Publish = pPublish;
	else 
		return -1;
	return 0;
}

int CRtmpRoom::Disband()
{
	
	
	return 0;
}

int CRtmpRoom::BroadcastVideo(CVideoMessage* pMsg)
{
	m_Msgs.push_back(pMsg);
	Refresh();
	return 0;
}

int CRtmpRoom::BroadcastAudio(CAudioMessage* pMsg)
{
	m_Msgs.push_back(pMsg);
	Refresh();
	return 0;
}

int CRtmpRoom::BroadcastMsg(CBaseMessage* pMsg)
{
	//
	
	return 0;
}

int CRtmpRoom::Refresh()
{
	return 0;
}
