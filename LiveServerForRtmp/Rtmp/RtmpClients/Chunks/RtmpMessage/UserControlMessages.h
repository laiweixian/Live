#pragma once
#include "../Receive/BaseMessage.h"


#define ERR_NO_EXIST_CONTROL	-1
#define SERVER_NO_RECEIVE		-2


class CUserControlMessages 
{
protected:
	CUserControlMessages();
	 ~CUserControlMessages();
public:
	struct Object {};
	static Object* Decode(CBaseMessage* pMsg);
	static CBaseMessage* Encode(uint32_t timestamp, uint32_t msid, Object obj);
	static void FreeObject(Object** ppObj);
};