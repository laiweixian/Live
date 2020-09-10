#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

class CCommandReceiveVideo
{
public:
	CCommandReceiveVideo();
	virtual ~CCommandReceiveVideo();

	int HandleReceiveVideo(AMF0::CParse *parse);


};

