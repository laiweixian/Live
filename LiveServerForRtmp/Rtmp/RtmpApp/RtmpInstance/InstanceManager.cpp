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

CRtmpInstance* CInstanceManager::Connect(const char* appName, const char* instanceName)
{
	CRtmpInstance* pInst = NULL;
	auto it = m_Intances.begin();
	int ret = 0;

	if (strcmp(m_AppName.data(),appName) != 0)
		goto ERR_APP;

	for (it = m_Intances.begin();it!= m_Intances.end(); it++)
	{
		ret = (*it)->GetName().compare(instanceName);
		if (ret == 0)
			pInst = *it;
	}

	if (pInst == NULL)
		pInst = new CRtmpInstance(instanceName);

	return pInst;
ERR_APP:
	return NULL;
}