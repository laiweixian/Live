#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandVideo
{
public:
	CCommandVideo();
	virtual ~CCommandVideo();

	int HandleReceiveVideo(AMF0::CParse *parse);
};

