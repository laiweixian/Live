#pragma once

#include "stdafx.h"

class CFormatContext
{
public:
	CFormatContext(string path);
	virtual ~CFormatContext();

	AVFormatContext* &GetCtx();
	
public:
	int Init();
protected:
	string m_Path;
	AVFormatContext *m_Ctx;
};
