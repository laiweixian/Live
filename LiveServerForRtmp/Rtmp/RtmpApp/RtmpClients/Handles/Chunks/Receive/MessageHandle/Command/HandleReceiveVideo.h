#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

class CHandleReceiveVideo
{
protected:
	CHandleReceiveVideo();
	virtual ~CHandleReceiveVideo();

protected:
	int HandleReceiveVideo(AMF0::CParse *parse);
};