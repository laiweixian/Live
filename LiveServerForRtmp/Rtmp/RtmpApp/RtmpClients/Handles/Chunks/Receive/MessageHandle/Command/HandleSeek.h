#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleSeek
{
protected:
	CHandleSeek();
	virtual ~CHandleSeek();

protected:
	int HandleSeek(AMF0::CParse *parse);
};