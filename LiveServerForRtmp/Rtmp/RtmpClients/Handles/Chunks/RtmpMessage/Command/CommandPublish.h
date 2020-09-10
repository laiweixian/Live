#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandPublish
{
public:
	CCommandPublish();
	virtual ~CCommandPublish();

	int HandlePublish(AMF0::CParse *parse);
};

