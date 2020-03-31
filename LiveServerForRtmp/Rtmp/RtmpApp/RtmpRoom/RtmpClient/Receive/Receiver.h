#pragma once

#include "stdafx.h"

#include "Handshake/Handshake.h"
#include "Message/Message.h"

class IOutStream
{
protected:
	~IOutStream() = default;
public:
	IOutStream() = default;
	virtual int WriteToPeer(const void* src,const int srcLength) = 0;
};

class CReciever
{
public:
	CReciever(IOutStream* pOut);
	virtual ~CReciever();
	
	virtual int OnReceive(void* src, const int srcLength) = 0;
protected:
	IOutStream* m_OutStream;
};

