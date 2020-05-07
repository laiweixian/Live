#pragma once

#include "stdafx.h"

#include "RtmpClient/RtmpClient.h"

class CRtmpRoom 
{
public:
	CRtmpRoom();
	~CRtmpRoom();


private:
	CRtmpClient *m_Owner;
	vector<CRtmpClient*> m_Players;

};
