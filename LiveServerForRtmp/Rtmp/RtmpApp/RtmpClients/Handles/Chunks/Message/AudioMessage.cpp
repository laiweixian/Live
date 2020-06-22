#include "AudioMessage.h"

CAudioMessage::CAudioMessage()
{

}

CAudioMessage::~CAudioMessage()
{

}

int CAudioMessage::HandleAudioMessage(CBaseMessage* pMsg)
{
	return SetAudioMessage(pMsg);
}