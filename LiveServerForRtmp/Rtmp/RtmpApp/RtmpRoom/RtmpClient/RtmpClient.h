#pragma once

#include "Receive/Handshake/Handshake.h"
#include "Receive/Message/Messages.h"

class CRtmpClient : public CHandshake , public CMessages
{
public:
	CRtmpClient();
	~CRtmpClient();



private:
	
};
