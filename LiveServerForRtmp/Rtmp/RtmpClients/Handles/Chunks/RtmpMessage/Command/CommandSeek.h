#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandSeek
{
public:
	CCommandSeek();
	virtual ~CCommandSeek();

	int HandleSeek(AMF0::CParse *parse);
};

