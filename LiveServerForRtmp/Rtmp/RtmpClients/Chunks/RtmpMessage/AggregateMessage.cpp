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

uint8_t* CAggregateMessage::TranslatePayload(Object obj, uint32_t* outLength)
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


void CAggregateMessage::FreeObject(CAggregateMessage::Object** ppObj)
{
	delete (*ppObj);
	(*ppObj) = NULL;
}

CBaseMessage* CAggregateMessage::Encode(uint32_t timestamp, uint32_t msid, CAggregateMessage::Object obj)
{
	CBaseMessage *pMsg = NULL;
	uint8_t *payload = NULL;
	uint32_t length = 0;

	payload = TranslatePayload(obj, &length);
	
	pMsg = new CBaseMessage(AGGREGATE_MESSAGE_TYPE_ID,length,timestamp,msid,payload,length);
	delete[] payload;
	payload = NULL;
	return pMsg;
}
