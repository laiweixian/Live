#include "WindowAcknowledgementSize.h"

CWindowAcknowledgementSize::CWindowAcknowledgementSize()
{

}

CWindowAcknowledgementSize::~CWindowAcknowledgementSize()
{

}

CWindowAcknowledgementSize::Object* CWindowAcknowledgementSize::Decode(CBaseMessage* pMsg)
{
	CWindowAcknowledgementSize::Object* pObj = NULL;
	uint8_t buf[4] = {0};
	uint32_t winAckSize = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf,payload.bufSize);
	winAckSize = BigToHost32(buf);
	
	pObj = new CWindowAcknowledgementSize::Object;
	pObj->winAckSize = winAckSize;
	return pObj;
}

uint8_t* CWindowAcknowledgementSize::TranslatePayload(uint32_t winAckSize, uint32_t* outLength)
{
	uint8_t *buf = NULL;
	uint32_t bufLength = 0;
	uint32_t bNum = 0;

	bufLength = 4;
	buf = new uint8_t[bufLength];
	memset(buf, 0, bufLength);

	bNum = HostToBig32(winAckSize);
	memcpy(buf, &bNum, 4);

	*outLength = bufLength;
	return buf;
}

CBaseMessage* CWindowAcknowledgementSize::Encode(uint32_t timestamp, uint32_t msid, CWindowAcknowledgementSize::Object obj)
{
	CBaseMessage* pMsg = NULL;
	uint8_t *payload = NULL;
	uint32_t payloadLen = 0;

	payload = TranslatePayload(obj.winAckSize, &payloadLen);

	pMsg = new CBaseMessage(WINDOW_ACKNOWLEDGEMENT_SIZE_TYPE_ID,payloadLen,timestamp,msid,payload,payloadLen);

	delete[] payload;
	payload = NULL;
	payloadLen = 0;

	return pMsg;
}

void CWindowAcknowledgementSize::FreeObject(Object** ppObj)
{
	delete (*ppObj);
	*ppObj = NULL;
}