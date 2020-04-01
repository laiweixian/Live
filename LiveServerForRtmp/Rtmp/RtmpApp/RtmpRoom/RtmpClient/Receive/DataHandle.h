#pragma once

#include "stdafx.h"

enum DataHandleType
{
	INVALID, HANDSHAKE,CHUNK
};

class CDataHandle
{
public:
	CDataHandle() = default;
	virtual ~CDataHandle() = default;
	
	virtual int OnRequest(uint8_t* src, const int srcLength) = 0;
	virtual DataHandleType GetType() = 0;
	virtual void* GetResponse(int* outLen) const  = 0 ;
};

