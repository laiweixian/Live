#pragma once

#include "stdafx.h"

class CPlayer;
class CPublish;

class CRtmpRoom 
{
public:
	CRtmpRoom(string name,CPublish* pPublish);
	~CRtmpRoom();

	//
public:
	void BroadcastAudio(const char* src,const int srcLen);
	void BroadcastVideo(const char* src, const int srcLen);
	void BroadcastMsg(const char* src, const int srcLen);
	void Disband();

	//
public:
	void Enter(CPlayer* pPlayer);
	void Leave(CPlayer* pPlayer);


public:
	string GetName();
	
private:
	string m_Name;
	CPublish *m_Publish;

	vector<CPlayer*> m_Players;
	
};
