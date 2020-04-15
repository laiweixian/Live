#include "AudioMessage.h"

CAudioMessage::CAudioMessage(uint32_t csid, uint32_t ts, uint32_t msgLength, uint8_t msgTypeId, uint32_t msgStreamId) :\
CBaseMessage(csid,ts, msgLength, msgTypeId, msgStreamId)
{

}

CAudioMessage::~CAudioMessage()
{

}

CBaseMessage::MessageType CAudioMessage::GetType()
{
	return CBaseMessage::MessageType::AUDIO_MESSAGE;
}

CAudioMessage::Content* CAudioMessage::GetContent()
{
	CAudioMessage::Content *pContent = NULL;

	pContent = new CAudioMessage::Content;
	pContent->buffSize = m_Header.messageLength;
	pContent->buff = new uint8_t[pContent->buffSize];
	memcpy(pContent->buff,m_Payload.buff, pContent->buffSize);
	return pContent;
}

void CAudioMessage::Content_free(CAudioMessage::Content** ppContent)
{
	if (*ppContent == NULL)	return;
	if ((*ppContent)->buff)	delete[](*ppContent)->buff;
	(*ppContent)->buff = NULL;
	(*ppContent)->buffSize = 0;

	*ppContent = NULL;
}

