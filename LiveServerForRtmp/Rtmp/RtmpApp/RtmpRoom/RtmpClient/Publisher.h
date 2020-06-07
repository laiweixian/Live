#pragma once

#include "stdafx.h"
class CPlayer;

class CPublish
{
protected:
	CPublish();
	virtual ~CPublish();
public:
	void OnEnter(CPlayer* pPlayer);
	void OnLeave(CPlayer* pPlayer);

protected:
	virtual int CreateRoom() final;
	virtual int DestroyRoom() final;
};

