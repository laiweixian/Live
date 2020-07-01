#pragma once

#include "stdafx.h"
#include "RtmpInstance.h"


class CInstanceManager
{
protected:
	CInstanceManager(string appName);
	virtual ~CInstanceManager();

public:
	CRtmpInstance* Connect(const char* instanceName);

protected:
	int PreInitialize();
	int Initialize();
	int Run();
	int Pause();
	int Stop();

private:
	string m_AppName;
	vector<CRtmpInstance*> m_Intances;
};


