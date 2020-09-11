#pragma once
#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandClose
{
public:
	CCommandClose();
	virtual ~CCommandClose();

	int HandleClose(AMF0::CParse *parse);
};

