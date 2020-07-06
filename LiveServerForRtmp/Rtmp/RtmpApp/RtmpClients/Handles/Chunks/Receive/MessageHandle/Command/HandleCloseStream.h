#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleCloseStream
{
protected:
	CHandleCloseStream();
	virtual ~CHandleCloseStream();

protected:
	int HandleCloseStream(AMF0::CParse *parse);
};
