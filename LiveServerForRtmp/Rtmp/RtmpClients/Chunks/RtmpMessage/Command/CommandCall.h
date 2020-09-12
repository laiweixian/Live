#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandCall
{
public:
	CCommandCall();
	virtual ~CCommandCall();

	int HandleCall(AMF0::CParse *parse);

	
};

