#pragma once

#include "stdafx.h"

#include "Player.h"
#include "Publisher.h"


class CRtmpRoom 
{
private:
	CRtmpRoom();
	~CRtmpRoom();

public:
	static CRtmpRoom* Create(string name);

//property
	string GetName(); 
	
private:
	string m_Name;
};
