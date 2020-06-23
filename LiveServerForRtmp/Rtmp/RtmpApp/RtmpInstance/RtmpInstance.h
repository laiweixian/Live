#pragma once

#include "stdafx.h"
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"



class CRtmpInstance
{
public:
	CRtmpInstance(string name);
	~CRtmpInstance();
public:
	string GetName();

	int SetPublisher(CRtmpClient *pActor);
	int Enter(CRtmpClient *pAudience);
	int Leave(CRtmpClient *pClient);

	int BroadcastVideo(CRtmpClient *pActor ,CBaseMessage* pVideo);
	int BroadcastAudio(CRtmpClient *pActor, CBaseMessage* pVideo);
	int BroadcastMsg(CRtmpClient *pActor, CBaseMessage* pVideo);
private:
	string m_Name;

	CRtmpClient* m_Actor;
	vector<CRtmpClient*> m_Audiences;
};


