#pragma once

#include "../stdafx.h"

#define IO_PARENT_NAME	"io";

class CIOModule
{
public:
	CIOModule(bool active = false, char *ioname = NULL) :m_Active(active),m_IOName(ioname)  {}
	~CIOModule(){}

	virtual int Open() = 0;
	virtual int Read(const int ioId, char *buff, const int buffLen) = 0;
	virtual int Write(const int ioId, char *buff, const int buffLen) = 0;
	virtual int Close(const int ioId) = 0;

	virtual char* GetParentName() final { return IO_PARENT_NAME;}
	virtual char* GetIOName() final {return m_IOName; }
	virtual bool	GetActive() final {return m_Active;}
private:
	bool m_Active;
	char *m_IOName;
	
};





