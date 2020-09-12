#include "AudioMessage.h"

CAudioMessage::CAudioMessage()
{

}

CAudioMessage::~CAudioMessage()
{

}

int CAudioMessage::Handle(CBaseMessage* pMsg)
{
	return AudioMessageHandle(pMsg);
}