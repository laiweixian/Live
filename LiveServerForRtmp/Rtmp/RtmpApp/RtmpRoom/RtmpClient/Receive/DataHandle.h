#pragma once

#include "stdafx.h"
#include "DataHandleRespose.h"





class CDataHandle
{
public:
	CDataHandle(IDataHandleRespose* pRespose);
	virtual ~CDataHandle() ;
	
	virtual int OnRequest(uint8_t* src, const int srcLength) = 0;
	virtual DataHandleType GetType() = 0;
protected:
	IDataHandleRespose *m_Respose;
};

