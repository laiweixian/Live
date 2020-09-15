#include "AggregateMessage.h"

CAggregateMessage::CAggregateMessage()
{

}

CAggregateMessage::~CAggregateMessage()
{

}

CAggregateMessage::Object* CAggregateMessage::Decode(CBaseMessage* pMsg)
{
	return NULL;
}

uint8_t* CAggregateMessage::TranslatePayload(uint32_t sequenceNumber, uint32_t* outLength)
{
	uint8_t *buf = NULL;
	uint32_t bufLength = 0;
	uint32_t bNum = 0;

	bufLength = 4;
	buf = new uint8_t[bufLength];
	memset(buf, 0, bufLength);

	bNum = HostToBig32(sequenceNumber);
	memcpy(buf, &bNum, 4);

	*outLength = bufLength;
	return buf;
 }

