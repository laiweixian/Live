#pragma once

#include "stdafx.h"

class IHandleBaseEvent
{
protected:
	virtual ~IHandleBaseEvent() = default;
public:
	IHandleBaseEvent() = default;
};
