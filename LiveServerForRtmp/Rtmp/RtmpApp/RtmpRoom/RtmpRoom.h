#pragma once

#include "../../../stdafx.h"

#include "RtmpClient/RtmpClient.h"

class CRtmpRoom
{
public:
	CRtmpRoom(const char* roomName); 
	~CRtmpRoom();

	void JoinIn(CRtmpClient* client);
	void Leave(CRtmpClient* client);

private:
	vector<CRtmpClient*> m_Clients;

};
