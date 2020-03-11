#pragma once

#include "Modules/BaseModule.h"
#include "Modules/IOStreams/BaseIOStream.h"

#define IO_MODULE_NAME	"io"

class CBaseIOStreamModule final: public CBaseModule
{
private:
	CBaseIOStreamModule();
	~CBaseIOStreamModule();
public:
	static CBaseIOStreamModule* GetInstance();
	
	ULONG RegisterIOStream(CBaseIOStream* piostream);

public:
	//CBaseModule
	ULONG Init();
	ULONG Run();
	ULONG Release();
	const char* GetBaseModuleName();
public:
	static CBaseIOStreamModule* S_IOModule;
	vector<CBaseIOStream*> m_IOStreams;
};
ULONG register_io_stream(CBaseIOStream* piostream);

