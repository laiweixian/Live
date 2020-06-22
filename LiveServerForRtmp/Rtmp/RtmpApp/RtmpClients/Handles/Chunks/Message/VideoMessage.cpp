#include "VideoMessage.h"

CVideoMessage::CVideoMessage()
{

}

CVideoMessage::~CVideoMessage()
{

}

int CVideoMessage::HandleVideoMessage(CBaseMessage* pMsg)
{
	return SetVideoMessage(pMsg);
}