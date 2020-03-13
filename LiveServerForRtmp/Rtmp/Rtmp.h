#pragma once


#include "RtmpApp/RtmpApp.h"

class CRtmp 
{
public:
	CRtmp();
	~CRtmp();
private:
	void Init() ;
	void Run() ;
	 
private:
	CRtmpApp *m_App;
};