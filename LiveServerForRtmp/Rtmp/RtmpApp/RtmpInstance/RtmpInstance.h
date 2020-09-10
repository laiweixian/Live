#pragma once

#include "stdafx.h"

#include "VideoCodec.h"
#include "AudioCodec.h"


#define ERR_ACTOR_EXIST			-1
#define ERR_AUDIENCE_REPEAT		-2
#define ERR_ACTOR_NO_MATCH		-3

class CRtmpClient;

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

	//int BroadcastVideo(CRtmpClient *pActor ,CRtmpMessage* pVideo);
	//int BroadcastAudio(CRtmpClient *pActor,CRtmpMessage* pVideo);
	//int BroadcastMsg(CRtmpClient *pActor,CRtmpMessage* pVideo);

private:
	int ActorLeave();
	int AudienceLeave(CRtmpClient *pAudience);

	int Init();
	
private:
	string m_Name;

	CRtmpClient *m_Actor;
	vector<CRtmpClient*> m_Audiences;
	
	CVideoCodec* m_Video;
};


