#pragma once

#include "../CoreModule.h"
#include "RtmpApp/RtmpApp.h"

class CRtmp : public CCoreModule
{
public:
	CRtmp();
	~CRtmp();
private:

	//CCoreModule
	 int InitCore() ;
	 int RunCore() ;
	 int RemoveCore();
private:
	vector<CRtmpModule*> m_Apps;
	
};