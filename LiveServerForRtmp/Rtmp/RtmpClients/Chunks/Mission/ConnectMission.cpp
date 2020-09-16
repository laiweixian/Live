#include "ConnectMission.h"

CConnectMission::CConnectMission() :m_Active(false), m_Obj({0})
{

}

CConnectMission::~CConnectMission()
{

}

void CConnectMission::Active()
{
	if (!m_Active)
		m_Active = true;
}

void CConnectMission::InActive()
{
	if (m_Active)
		m_Active = false;
}

void CConnectMission::SetCommandConnect(CCommandConnect::Object *pObj)
{
	memcpy(m_Obj.rtmpUrl,pObj->tcUrl,1024);
}

void CConnectMission::SetWinAckSize(CWindowAcknowledgementSize::Object *pObj)
{
	//
	
}

int CConnectMission::Continue()
{
	return -1;
}

bool CConnectMission::Complete()
{
	return false;
}

int CConnectMission::SendAckWinSize()
{
	return -1;
}

int CConnectMission::SendSetPeerBandwidth()
{
	return -1;
}

int CConnectMission::SendUserControlMessage()
{
	return -1;
}

int CConnectMission::SendConnectResponse()
{
	return -1;
}