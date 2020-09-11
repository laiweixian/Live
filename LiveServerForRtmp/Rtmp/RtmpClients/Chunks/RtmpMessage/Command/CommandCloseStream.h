#pragma once
#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandCloseStream
{
public:
	CCommandCloseStream();
	virtual ~CCommandCloseStream();

	int HandleCloseStream(AMF0::CParse *parse);
};

