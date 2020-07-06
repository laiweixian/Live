#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleDeleteStream
{
protected:
	CHandleDeleteStream();
	virtual ~CHandleDeleteStream();
protected:
	int HandleDeleteStream(AMF0::CParse *parse);
};
