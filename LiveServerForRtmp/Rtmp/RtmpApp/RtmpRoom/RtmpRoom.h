#pragma once

#include "stdafx.h"

#include "RtmpClient/Handles/Chunks/RtmpMessage/RtmpMessage.h"

class CPlayer;
class CPublisher;
class IRoom4Player;
class IRoom4Publisher;

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
	 int Disband() = 0;
	 int BroadcastVideo(CVideoMessage* pMsg);
	 int BroadcastAudio(CAudioMessage* pMsg);
	 int BroadcastMsg(CBaseMessage* pMsg);
private:
	int Refresh();
private:
	string m_Name;
	
	CPublisher *m_Publish;
	vector<CPlayer*> m_Players;
	vector<CBaseMessage*> m_Msgs;
};

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
	virtual int BroadcastVideo(const uint8_t* src, const int srcLen) = 0 ;
	virtual int BroadcastAudio(const uint8_t* src, const int srcLen) = 0;
	virtual int BroadcastMsg(const uint8_t* src, const int srcLen) = 0;
};

