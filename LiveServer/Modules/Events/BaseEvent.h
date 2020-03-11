#pragma once

#include "stdafx.h"
#include "Modules/IOStreams/IONotification.h"

class CBaseEvent;
extern ULONG register_event(CBaseEvent* pEvent);

class CBaseEvent : public CIONotification
{
public:
	CBaseEvent();
	virtual ~CBaseEvent();

	virtual ULONG Init() = 0;
	virtual ULONG Run() = 0;
	virtual ULONG Release() = 0;
};





