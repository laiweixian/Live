#pragma once

#include "stdafx.h"

class CBaseModule;
extern ULONG register_base_module(CBaseModule *pBase);

class CBaseModule
{
public:
	CBaseModule() {}
	virtual ~CBaseModule() {}

	virtual ULONG Init() = 0;
	virtual ULONG Run() = 0;
	virtual ULONG Release() = 0;

	virtual const char* GetBaseModuleName() = 0;
};