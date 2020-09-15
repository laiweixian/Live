#pragma once

class CBaseProcess
{
protected:
	CBaseProcess();
	virtual ~CBaseProcess();

public:
	virtual int Process() = 0;
};
