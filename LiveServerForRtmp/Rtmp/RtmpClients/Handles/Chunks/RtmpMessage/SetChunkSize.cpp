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
	CBaseMessage::Payload* payload = pMsg->GetPayload();

	memcpy(buf, payload->buf,payload->bufSize);
	chunkSize = BigToHost32(buf);
	return SetChunkSizeHandle(chunkSize);
}