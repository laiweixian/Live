#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandPlay2
{
public:
	CCommandPlay2();
	virtual ~CCommandPlay2();

	int HandlePlay2(AMF0::CParse *parse);
};

