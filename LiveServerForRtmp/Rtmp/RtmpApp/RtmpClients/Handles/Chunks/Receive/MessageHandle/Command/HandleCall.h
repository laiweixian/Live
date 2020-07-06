#pragma once
#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleCall
{
protected:
	CHandleCall();
	virtual ~CHandleCall();
protected:
	int HandleCall(AMF0::CParse *parse);
};
