#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandlePublish
{
protected:
	CHandlePublish();
	virtual ~CHandlePublish();

protected:
	int HandlePublish(AMF0::CParse *parse);
};