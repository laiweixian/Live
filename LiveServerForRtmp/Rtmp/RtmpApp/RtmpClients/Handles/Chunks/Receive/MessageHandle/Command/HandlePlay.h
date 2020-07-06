#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandlePlay
{
protected:
	CHandlePlay();
	virtual ~CHandlePlay();
protected:
	int HandlePlay(AMF0::CParse *parse);
};
