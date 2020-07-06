#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandlePause
{
protected:
	CHandlePause();
	virtual ~CHandlePause();
protected:
	int HandlePause(AMF0::CParse *parse);
};