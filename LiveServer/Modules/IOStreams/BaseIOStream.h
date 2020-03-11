#pragma once

#include "stdafx.h"
#include "Modules/IOStreams/IONotification.h"

class CBaseIOStream;
extern ULONG register_io_stream(CBaseIOStream* pIo);
enum EIOPos{BEGIN,END,CUR};

class CBaseIOStream
{
public:
	CBaseIOStream() {}
	virtual ~CBaseIOStream() {}

	virtual ULONG Init() = 0;
	virtual ULONG Run() = 0;
	virtual ULONG Release() = 0;

	virtual const char* GetIOStreamName() = 0;
	virtual BOOL Active() = 0;

	//
	virtual ULONG Open() = 0;
	virtual ULONG Read(const int ioID, char* dst, const int dstLen) = 0;
	virtual ULONG Write(const int ioID, char* dst, const int dstLen) = 0;
	virtual ULONG Seek(const int ioID, EIOPos pos, const int offset) = 0;
	virtual ULONG Close(const int ioID) = 0;
};

