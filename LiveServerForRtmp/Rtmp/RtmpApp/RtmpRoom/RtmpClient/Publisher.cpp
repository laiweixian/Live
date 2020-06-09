#include "Player.h"
#include "Publisher.h"
#include "../RtmpRooms.h"

CPublish::CPublish() : m_Name(""),m_Room(NULL)
{

}

CPublish::~CPublish()
{

}

void CPublish::OnEnter(CPlayer* pPlayer)
{

}

void CPublish::OnLeave(CPlayer* pPlayer)
{

}

int CPublish::CreateRoom(string name)
{
	CRtmpRooms* pInstance = NULL;
	CRtmpRoom *pRoom = NULL;

	if (m_Room)
		return PUBLISHER_OK;

	pInstance = CRtmpRooms::GetInstance();
	pRoom = pInstance->CreateRoom(name,this);
	if (pRoom == NULL)
		goto fail;

	m_Room = pRoom;
	m_Room->SetOwner(this);
	return PUBLISHER_OK;
	
fail:
	return PUBLISHER_FAILURE;
}

int CPublish::DestroyRoom()
{
	if (m_Room == NULL)
		return PUBLISHER_FAILURE;

	m_Room->DisbandRoom(this);
	m_Room = NULL;
	return PUBLISHER_OK;
}

int CPublish::BroadcastVideo(const char* src, const int srcLen)
{	
	if (!m_Room)	return PUBLISHER_FAILURE;
	m_Room->BroadcastVideo(this,src,srcLen);
	return PUBLISHER_OK;
}

int CPublish::BroadcastAudio(const char* src, const int srcLen)
{
	if (!m_Room)	return PUBLISHER_FAILURE;
	m_Room->BroadcastAudio(this,src,srcLen);
	return PUBLISHER_OK;
}

int CPublish::BroadcastMsg(const char* src, const int srcLen)
{
	if (!m_Room)	return PUBLISHER_FAILURE;
	m_Room->BroadcastMsg(this,src,srcLen);
	return PUBLISHER_OK;
}

