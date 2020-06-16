#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"


class CPlayer;
class CPublisher;

class IRoom4Player
{
protected:
	IRoom4Player() = default;
	virtual ~IRoom4Player() = default;
public:
	virtual int Join(CPlayer* pPlayer) = 0;
	virtual int Leave(CPlayer* pPlayer) = 0;
};

class IRoom4Publisher
{
protected:
	IRoom4Publisher() = default;
	virtual ~IRoom4Publisher() = default;
public:
	virtual int SetOwner(CPublisher *pPublish) = 0;
	virtual int Disband() = 0;
	virtual int BroadcastVideo(CBaseMessage* pMsg) = 0;
	virtual int BroadcastAudio(CBaseMessage *pMsg) = 0;
	virtual int BroadcastMsg(CBaseMessage *pMsg) = 0;
};

class CRtmpRoom : public IRoom4Player,public IRoom4Publisher
{
public:
	CRtmpRoom(string name);
	~CRtmpRoom();

	//IRoom4Player
public:
	 int Join(CPlayer* pPlayer);
	 int Leave(CPlayer* pPlayer);

	 //IRoom4Publisher
	 int SetOwner(CPublisher *pPublish);
	 int Disband() ;
	 int BroadcastVideo(CBaseMessage* pMsg);
	 int BroadcastAudio(CBaseMessage* pMsg);
	 int BroadcastMsg(CBaseMessage* pMsg);
private:
	int Refresh();
private:
	string m_Name;
	
	CPublisher *m_Publish;
	vector<CPlayer*> m_Players;
	vector<CBaseMessage*> m_Msgs;
};



