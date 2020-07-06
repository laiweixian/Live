#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleClose
{
protected:
	CHandleClose();
	virtual ~CHandleClose();

protected:
	int HandleClose(AMF0::CParse *parse);
};
