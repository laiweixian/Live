#pragma once
#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleReceiveAudio
{
protected:
	CHandleReceiveAudio();
	virtual ~CHandleReceiveAudio();

protected:
	int HandleReceiveAudio(AMF0::CParse *parse);
};
