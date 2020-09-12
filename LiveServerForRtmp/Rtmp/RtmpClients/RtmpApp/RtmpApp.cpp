#include "RtmpApp.h"

CRtmpApp::CRtmpApp(string name):m_Name(name)
{

}

CRtmpApp::~CRtmpApp()
{
	auto it = m_Instances.begin();
	for (it = m_Instances.begin(); it != m_Instances.end(); it++)
	{
		delete (*it);
		*it = NULL;
	}
	m_Instances.clear();
}

int CRtmpApp::Initialize()
{
	return 0;
}

int CRtmpApp::Run()
{
	return -1;
}




