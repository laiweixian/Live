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

void CConnectMission::Activate()
{
	if (!m_Active)
	{
		m_Active = true;
	}
		
}

void CConnectMission::InActivate()
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

int CConnectMission::Run()
{
	int ret = -1;
	switch (m_RStat)
	{
	case CConnectMission::R_NONE:
		ret = -1;
		break;
	case CConnectMission::R_COMMAND_CONNENCT:
		ret = SendAckWinSize();	
		ret = SendSetPeerBandwidth(); 
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



int CConnectMission::SendAckWinSize()
{
	CBaseMessage* pMsg = NULL;
	CWindowAcknowledgementSize::Object obj;
	int ret = 0;
	uint32_t ts = ::GetTimestamp();

	obj.winAckSize = WIN_ACK_SIZE_VALUE;
	pMsg = CWindowAcknowledgementSize::Encode(0, 0, obj);
	ret = Send2MySelf(pMsg);
	return ret;
}

int CConnectMission::SendSetPeerBandwidth()
{
	CBaseMessage* pMsg = NULL;
	CSetPeerBandwidth::Object obj;
	int ret = 0;

	obj.ackWinSize = WIN_ACK_SIZE_VALUE;
	obj.limitType = 1;
	pMsg = CSetPeerBandwidth::Encode(0, 0, obj);

	ret = Send2MySelf(pMsg);
	return ret;
}

int CConnectMission::SendUserControlMessage()
{
	CBaseMessage *pMsg = NULL;
	CStreamBegin::Object obj;
	CUserControlMessages::Object userObj;
	int ret = -1;

	obj.streamID = GetStreamID();
	
	userObj.eType = CUserControlMessages::STREAM_BEGIN;
	userObj.eData = &obj;

	pMsg = CUserControlMessages::Encode(0, 0, userObj);
	
	ret = Send2MySelf(pMsg);
	return ret;
}

int CConnectMission::SendConnectResponse()
{
	return -1;
}