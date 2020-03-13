#pragma once

#include "Rtmp/RtmpApp/RtmpRoom/RtmpClient/RtmpMessages/RtmpMessage/Chunk/chunk.h"

class CRtmpMessages
{
public:
	CRtmpMessages();
	~CRtmpMessages();

private:
	int OnReceive(char *buff, const int buffLen);

	
	
};