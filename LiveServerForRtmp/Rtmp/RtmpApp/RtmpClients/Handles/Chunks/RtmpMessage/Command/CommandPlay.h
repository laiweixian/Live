#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandPlay
{
public:
	CCommandPlay();
	virtual ~CCommandPlay();

	int HandlePlay(AMF0::CParse *parse);
};

