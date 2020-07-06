#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleCreateStream
{
protected:
	CHandleCreateStream();
	virtual ~CHandleCreateStream();

protected:
	int HandleCreateStream(AMF0::CParse *parse);

};
