#pragma once

#include "Handles/Handshake/Handshake.h"
#include "Handles/Message/Messages.h"


class CRtmpClient : public CHandshake , public CMessages
{
public:
	CRtmpClient(uint32_t chunkSize);
	~CRtmpClient();



private:
	
};
