#pragma once

#include "stdafx.h"
#include "RtmpApp/RtmpApp.h"

class CRtmp 
{
public:
	CRtmp();
	~CRtmp();
public:

	void PreInit();
	void Init() ;
	void Run();
	 
private:
	CRtmpApp *m_App;
};