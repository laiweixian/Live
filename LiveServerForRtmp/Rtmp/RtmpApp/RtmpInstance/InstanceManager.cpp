#include "InstanceManager.h"

CInstanceManager::CInstanceManager(string appName):m_AppName(appName)
{

}

CInstanceManager::~CInstanceManager()
{

}


int CInstanceManager::PreInitialize()
{
	return 0;
}	

int CInstanceManager::Initialize()
{
	return 0;
}

int CInstanceManager::Run()
{
	return 0;
}

int CInstanceManager::Pause()
{
	return 0;
}

int CInstanceManager::Stop()
{
	return 0;
}

CRtmpInstance* CInstanceManager::Connect(const char* instanceName)
{
	CRtmpInstance* pInst = NULL;
	auto it = m_Intances.begin();
	int ret = 0;


	for (it = m_Intances.begin();it!= m_Intances.end(); it++)
	{
		ret = (*it)->GetName().compare(instanceName);
		if (ret == 0)
			pInst = *it;
	}

	if (pInst == NULL)
	{
		pInst = new CRtmpInstance(instanceName);
		m_Intances.push_back(pInst);
	}
		
	return pInst;
ERR_APP:
	return NULL;
}