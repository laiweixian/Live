#include "HandleAudioMessage.h"

CHandleAudioMessage::CHandleAudioMessage()
{

}

CHandleAudioMessage::~CHandleAudioMessage()
{

}

int CHandleAudioMessage::Handle(CBaseMessage* pMsg)
{
	return SetAudioMessage(pMsg);
}