#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandReceiveAudio
{
public:
	CCommandReceiveAudio();
	virtual ~CCommandReceiveAudio();

	int HandleReceiveAudio(AMF0::CParse *parse);
};

