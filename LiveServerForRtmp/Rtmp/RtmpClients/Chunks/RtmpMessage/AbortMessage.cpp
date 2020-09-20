#include "AbortMessage.h"

CAbortMessage::CAbortMessage()
{

}

CAbortMessage::~CAbortMessage()
{

}



CAbortMessage::Object* CAbortMessage::Decode(CBaseMessage* pMsg)
{
	CAbortMessage::Object* pObj = NULL;
	uint8_t buf[4] = { 0 };
	uint32_t csid = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf, payload.bufSize);
	csid = BigToHost32(buf);

	pObj = new CAbortMessage::Object;
	pObj->csid = csid;
	return pObj;
}

void CAbortMessage::FreeObject(Object** ppObj)
{
	delete (*ppObj);
	*ppObj = NULL;
}

uint8_t* CAbortMessage::TranslatePayload(Object obj, uint32_t* outLength)
{
	uint8_t *buf = NULL;
	uint32_t bufLength = 0;
	uint32_t bNum = 0; 

	bufLength = 4;
	buf = new uint8_t[bufLength];
	memset(buf,0,bufLength);

	bNum = HostToBig32(obj.csid);
	memcpy(buf,&bNum,4);

	*outLength = bufLength;
	return buf;
}

CBaseMessage* CAbortMessage::Encode(uint32_t timestamp, uint32_t msid, CAbortMessage::Object obj)
{
	uint8_t *payload = NULL;
	uint32_t length = 0;
	CBaseMessage *pMsg = NULL;

	payload = TranslatePayload(obj, &length);
	pMsg = new CBaseMessage(ABORT_MESSAGE_TYPE_ID,length,timestamp,msid,payload,length);

	delete[] payload;
	payload = NULL;
	return pMsg;
}