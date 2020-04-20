#pragma once

#include "stdafx.h"

#include "RtmpClient/RtmpClient.h"

class CRtmpRoom 
{
public:
	CRtmpRoom();
	~CRtmpRoom();

	void SetOwner(CRtmpClient* pOwner, const char* name);
	
	


	
	

private:
	CRtmpClient *m_Owner;
	vector<CRtmpClient*> m_Players;

};
