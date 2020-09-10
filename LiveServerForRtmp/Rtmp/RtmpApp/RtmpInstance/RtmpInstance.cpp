#include "RtmpInstance.h"
#include "Rtmp/RtmpApp/RtmpClients/RtmpClient.h"

CRtmpInstance::CRtmpInstance(string name):
				m_Name(name)
{
	
}

CRtmpInstance::~CRtmpInstance()
{

}

int CRtmpInstance::Init()
{
	int ret = 0;

	return 0;
}

string CRtmpInstance::GetName()
{
	return m_Name;
}

int CRtmpInstance::SetPublisher(CRtmpClient *pActor)
{
	if (m_Actor != NULL)
		return ERR_ACTOR_EXIST;
	m_Actor = pActor;
	return 0;
}

int CRtmpInstance::Enter(CRtmpClient *pAudience)
{
	auto it = m_Audiences.begin();
	for (it=m_Audiences.begin();it!= m_Audiences.end(); it++)
	{
		if (pAudience == *it)
			return ERR_AUDIENCE_REPEAT;
	}

	m_Audiences.push_back(pAudience);
	return 0;
}

int CRtmpInstance::Leave(CRtmpClient *pClient)
{	
	auto it = m_Audiences.begin();
	int ret = 0;
	if (pClient == m_Actor)
		ret = ActorLeave();
	else
		ret = AudienceLeave(pClient);
	return ret;
}



int CRtmpInstance::ActorLeave()
{
	return -1;
}

int CRtmpInstance::AudienceLeave(CRtmpClient *pAudience)
{
	return -1;
}



