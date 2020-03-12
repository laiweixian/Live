#pragma once

#include "../stdafx.h"

#define RTMP_PARENT_NAME "rtmp"

class CRtmpModule
{
public:
	CRtmpModule() = default;
	virtual ~CRtmpModule() = default;

	virtual int InitRtmp() = 0;
	virtual int RunRtmp() = 0;
	virtual int RemoveRtmp() = 0;
	virtual char* GetRtmpName() = 0;

	virtual char* GetParentName() final {
		return RTMP_PARENT_NAME;
	}
	
};
