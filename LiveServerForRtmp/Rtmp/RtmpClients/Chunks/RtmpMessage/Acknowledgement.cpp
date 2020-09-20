#include "Acknowledgement.h"

CAcknowledgement::CAcknowledgement()
{

}

CAcknowledgement::~CAcknowledgement()
{

}

CAcknowledgement::Object* CAcknowledgement::Decode(CBaseMessage* pMsg)
{
	CAcknowledgement::Object* pObj = NULL;
	uint8_t buf[4] = { 0 };
	uint32_t sequenceNumber = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf, payload.bufSize);
	sequenceNumber = BigToHost32(buf);

	pObj = new CAcknowledgement::Object;
	pObj->sequenceNumber = sequenceNumber;
	return pObj;
}

void CAcknowledgement::FreeObject(Object** ppObj)
{
	delete (*ppObj);
	*ppObj = NULL;
}

uint8_t* CAcknowledgement::TranslatePayload(CAcknowledgement::Object obj, uint32_t* outLength)
{
	uint8_t *buf = NULL;
	uint32_t bufLength = 0;
	uint32_t bNum = 0;

	bufLength = 4;
	buf = new uint8_t[bufLength];
	memset(buf, 0, bufLength);

	bNum = HostToBig32(obj.sequenceNumber);
	memcpy(buf, &bNum, 4);

	*outLength = bufLength;
	return buf;
}

CBaseMessage* CAcknowledgement::Encode(uint32_t timestamp, uint32_t msid, CAcknowledgement::Object obj)
{
	CBaseMessage *pMsg = NULL;
	uint8_t *payload = NULL;
	uint32_t length = 0;

	payload = TranslatePayload(obj, &length);
	pMsg = new CBaseMessage(ACKNOWLEDGEMENT_TYPE_ID,length,timestamp,msid,payload,length);

	delete[] payload;
	payload = NULL;

	return pMsg;
}
