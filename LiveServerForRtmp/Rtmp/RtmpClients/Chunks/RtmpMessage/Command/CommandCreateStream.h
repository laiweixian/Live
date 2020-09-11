#pragma once
#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandCreateStream
{
public:
	CCommandCreateStream();
	virtual ~CCommandCreateStream();

	int HandleCreateStream(AMF0::CParse *parse);
};

