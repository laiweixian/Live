#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandlePlay2
{
protected:
	CHandlePlay2();
	virtual ~CHandlePlay2();
protected:
	int HandlePlay2(AMF0::CParse *parse);
};

