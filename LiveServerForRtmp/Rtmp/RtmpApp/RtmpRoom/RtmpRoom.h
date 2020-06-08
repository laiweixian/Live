#pragma once

#include "stdafx.h"

class CPlayer;
class CPublish;

class CRtmpRoom 
{
public:
	CRtmpRoom(string name);
	~CRtmpRoom();

	//interface for publisher
public:
	int SetOwner(CPublish* pPublish);
	int BroadcastAudio(CPublish* pPublish,const char* src,const int srcLen);
	int BroadcastVideo(CPublish* pPublish,const char* src, const int srcLen);
	int BroadcastMsg(CPublish* pPublish,const char* src, const int srcLen);
	int DisbandRoom(CPublish* pPublish);

	//interface for player
public:
	int Enter(CPlayer* pPlayer);
	int Leave(CPlayer* pPlayer);

public:
	string GetName();
	int GetCount();
	CPlayer* GetPlayer(int index);
	
private:
	string m_Name;
	CPublish *m_Publish;
	vector<CPlayer*> m_Players;
};
