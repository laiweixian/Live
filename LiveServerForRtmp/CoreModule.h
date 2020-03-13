#pragma once

#include "stdafx.h"

#define CORE_PARENT_NAME	"/"

class CCoreModule
{
public:
	CCoreModule(bool active = false,char *name = NULL) : m_Active(false),m_CoreName(name){}
	virtual ~CCoreModule() {
		if(!m_CoreName)
			delete[] m_CoreName;
		m_CoreName = NULL;
	}

	virtual int PreInit() = 0;
	virtual int Init() = 0;
	virtual int InitComlete() = 0;
	virtual int Run() = 0;
	virtual int RunStop() = 0;

	
	virtual char* GetParentName() final {
		return CORE_PARENT_NAME;
	}
	virtual char* GetCoreName() final {
		return m_CoreName;
	}
	virtual bool GetActive() final
	{
		return m_Active;
	}

protected:
	bool m_Active;
	char* m_CoreName;
};