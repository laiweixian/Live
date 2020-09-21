#pragma once

class IBaseMission
{
protected:
	IBaseMission() = default;
	virtual ~IBaseMission() = default;
public:
	virtual void Activate() = 0;
	virtual int  Run() = 0;
	virtual void InActivate() = 0;
};
