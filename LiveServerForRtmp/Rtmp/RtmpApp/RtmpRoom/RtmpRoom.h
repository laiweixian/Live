#pragma once

#include "stdafx.h"

#include "RtmpClient/RtmpClient.h"

class CRtmpRoom
{
public:
	CRtmpRoom(const char* roomName, CRtmpClient* pMaster);
	~CRtmpRoom();

	void JoinIn(CRtmpClient* pClient);
	
private:
	vector<CRtmpClient*> m_Clients;

};
