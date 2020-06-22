#pragma once

#include "stdafx.h"
#include "RtmpApp/RtmpApp.h"

class CRtmp 
{
public:
	CRtmp();
	~CRtmp();
public:

	int PreInitialize();
	int Initialize();
	int Run();
	int Pause();
	int Stop();
	 
private:
	CRtmpApp *m_App;
};