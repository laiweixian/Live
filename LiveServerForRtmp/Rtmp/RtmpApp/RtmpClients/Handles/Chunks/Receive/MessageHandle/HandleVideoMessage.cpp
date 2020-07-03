#include "HandleVideoMessage.h"

CHandleVideoMessage::CHandleVideoMessage()
{

}

CHandleVideoMessage::~CHandleVideoMessage()
{

}

int CHandleVideoMessage::Handle(CBaseMessage* pMsg)
{
	return SetVideoMessage(pMsg);
}