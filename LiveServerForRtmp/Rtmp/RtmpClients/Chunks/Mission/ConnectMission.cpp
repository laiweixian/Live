#include "ConnectMission.h"

#define WIN_ACK_SIZE_VALUE 1024000

CConnectMission::CConnectMission() :m_Active(false), m_Obj({0}),\
									m_SStat(CConnectMission::SendStat::S_NONE),
									m_RStat(CConnectMission::ReceiveStat::R_NONE)
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
	if (m_RStat == CConnectMission::ReceiveStat::R_NONE)
	{
		memcpy(m_Obj.rtmpUrl, pObj->tcUrl, 1024);
		m_RStat = CConnectMission::ReceiveStat::R_COMMAND_CONNENCT;
	}
	
}

void CConnectMission::SetWinAckSize(CWindowAcknowledgementSize::Object *pObj)
{
	//
	if (m_RStat == CConnectMission::ReceiveStat::R_COMMAND_CONNENCT)
	{
		m_Obj.winAckSize = pObj->winAckSize;
		m_RStat = CConnectMission::ReceiveStat::R_WIN_ACK_SIZE;
	}
	
}

int CConnectMission::Continue()
{
	int ret = -1;
	switch (m_RStat)
	{
	case CConnectMission::R_NONE:
		ret = -1;
		break;
	case CConnectMission::R_COMMAND_CONNENCT:
		ret += SendAckWinSize();
		ret += SendSetPeerBandwidth();
		break;
	case CConnectMission::R_WIN_ACK_SIZE:
		ret += SendUserControlMessage();
		ret += SendConnectResponse();
		break;
	default:
		ret = -1;
		break;
	}


	return ret;
}

bool CConnectMission::Complete()
{
	const bool a = (m_RStat == CConnectMission::ReceiveStat::R_WIN_ACK_SIZE);
	const bool b = (m_SStat == CConnectMission::SendStat::S_CONNECT_RESPONSE);
	return( a&& b );
}

int CConnectMission::SendAckWinSize()
{
	CBaseMessage* pMsg = NULL;
	CWindowAcknowledgementSize::Object obj;
	
	obj.winAckSize = WIN_ACK_SIZE_VALUE;
	pMsg = CWindowAcknowledgementSize::Encode(0, 0, obj);
	return SendMessage(pMsg);
}

int CConnectMission::SendSetPeerBandwidth()
{
	CBaseMessage* pMsg = NULL;
	CSetPeerBandwidth::Object obj;

	obj.ackWinSize = WIN_ACK_SIZE_VALUE;
	obj.limitType = 1;
	pMsg = CSetPeerBandwidth::Encode(0, 0, obj);

	return SendMessage(pMsg);
}

int CConnectMission::SendUserControlMessage()
{
	CUserControlMessages::
	return ;
}

int CConnectMission::SendConnectResponse()
{
	return -1;
}