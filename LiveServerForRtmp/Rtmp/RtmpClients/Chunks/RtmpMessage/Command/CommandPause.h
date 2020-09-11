#pragma once
#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandPause
{
public:
	CCommandPause();
	virtual ~CCommandPause();

	int HandlePause(AMF0::CParse *parse);
};

