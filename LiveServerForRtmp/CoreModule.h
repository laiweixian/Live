#pragma once

#include "stdafx.h"

#define CORE_PARENT_NAME	"/"

class CCoreModule
{
public:
	CCoreModule() = default;
	virtual ~CCoreModule() = default;

	virtual int InitCore() = 0;
	virtual int RunCore() = 0;
	virtual int RemoveCore() = 0;

	virtual char* GetCoreName() = 0;
	virtual char* GetParentName() final {
		return CORE_PARENT_NAME;
	}
};