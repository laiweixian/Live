#include "RtmpInstance.h"

CRtmpInstance::CRtmpInstance(string name):m_Name(name)
{

}

CRtmpInstance::~CRtmpInstance()
{

}

string CRtmpInstance::GetName()
{
	return m_Name;
}

int CRtmpInstance::SetPublisher(CRtmpClient *pActor)
{
	return -1;
}

int CRtmpInstance::Enter(CRtmpClient *pAudience)
{
	return -1;
}

int CRtmpInstance::Leave(CRtmpClient *pClient)
{	
	return -1;
}

int CRtmpInstance::BroadcastVideo(CRtmpClient *pActor, CBaseMessage* pVideo)
{
	return -1;
}

int CRtmpInstance::BroadcastAudio(CRtmpClient *pActor, CBaseMessage* pVideo)
{
	return -1;
}

int CRtmpInstance::BroadcastMsg(CRtmpClient *pActor, CBaseMessage* pVideo)
{
	return -1;
}