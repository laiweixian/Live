#pragma once
#include "stdafx.h"

#include "Modules/BaseModule.h"
#include "Modules/Events/BaseEvent.h"

class CEventModule final : public CBaseModule
{
private:
	CEventModule();
public:
	CEventModule* GetInstance();

	//CBaseModule
	ULONG Init();
	ULONG Run();
	ULONG Release();
	const char* GetBaseModuleName();
public:
	static CEventModule* S_EventModuel;
private:
	vector<CBaseEvent*> m_Events;
};
ULONG register_event(CBaseEvent* pEvent);
