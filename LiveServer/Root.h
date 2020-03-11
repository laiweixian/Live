#pragma once

#include "Modules/BaseModule.h"

class CRoot
{
private:
	CRoot();
	~CRoot();
public:
	static CRoot* GetInstance();
	void Destory();
	ULONG RegisterBaseModule(CBaseModule* pModule);
public:
	
	static CRoot* S_Root;
	vector<CBaseModule*> m_BaseModules;
};
ULONG register_base_module(CBaseModule *pBase);

