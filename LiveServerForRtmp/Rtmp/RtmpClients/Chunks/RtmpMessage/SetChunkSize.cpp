#include "SetChunkSize.h"

CSetChunkSize::CSetChunkSize()
{

}

CSetChunkSize::~CSetChunkSize()
{

}

int CSetChunkSize::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t chunkSize = 0;
	CBaseMessage::Payload payload = pMsg->GetPayload();

	memcpy(buf, payload.buf, payload.bufSize);
	chunkSize = BigToHost32(buf);
	return SetChunkSizeHandle(chunkSize);
}

uint8_t* CSetChunkSize::TranslatePayload(uint32_t chunkSize, uint32_t* outLength)
{
	uint8_t *buf = NULL;
	uint32_t bufLength = 0;
	uint32_t bNum = 0;

	bufLength = 4;
	buf = new uint8_t[bufLength];
	memset(buf, 0, bufLength);

	bNum = HostToBig32(chunkSize);
	memcpy(buf, &bNum, 4);

	*outLength = bufLength;
	return buf;
}