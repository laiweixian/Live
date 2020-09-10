#pragma once
#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandDeleteStream
{
public:
	CCommandDeleteStream();
	virtual ~CCommandDeleteStream();

	int HandleDeleteStream(AMF0::CParse *parse);
};

