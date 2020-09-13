#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement()
{

}

CAcknowledgement::~CAcknowledgement()
{

}

int CAcknowledgement::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t sequenceNumber = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf, payload.bufSize);
	sequenceNumber = BigToHost32(buf);

	return AcknowledgementHandle(sequenceNumber);
}

uint8_t* CAcknowledgement::TranslatePayload(uint32_t sequenceNumber, uint32_t* outLength)
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
