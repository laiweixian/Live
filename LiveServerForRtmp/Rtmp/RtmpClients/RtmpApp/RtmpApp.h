#pragma once

#include "stdafx.h"
#include "RtmpInstance/RtmpInstance.h"

class CRtmpApp 
{
public:
	CRtmpApp(string name);
	~CRtmpApp();
public:
	int Initialize();
	int Run();

	//rtmp url :rtmp://localhost:1935/testapp/instance1
	CRtmpInstance* Search(string url);
	
	
	

private:
	
	
protected:
	

	
private:
	string m_Name;
	list<CRtmpInstance*> m_Instances;
};
