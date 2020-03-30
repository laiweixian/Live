#pragma once

#include "stdafx.h"


typedef int (*SendToPeer)(const void* src,const int srcLength);

class IReceive
{
public:
	IReceive(SendToPeer sendTo) : m_SendToPeer(sendTo) {}
	virtual ~IReceive() = default;

	virtual int OnReceive( void* src,const int srcLength) = 0;
protected:
	SendToPeer m_SendToPeer;
};

