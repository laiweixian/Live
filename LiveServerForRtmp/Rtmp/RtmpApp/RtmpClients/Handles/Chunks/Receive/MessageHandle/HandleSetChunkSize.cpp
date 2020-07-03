#include "HandleSetChunkSize.h"

CHandleSetChunkSize::CHandleSetChunkSize()
{

}

CHandleSetChunkSize::~CHandleSetChunkSize()
{

}

int CHandleSetChunkSize::Handle(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t chunkSize = 0;

	memcpy(buf,pMsg->GetData(),4);
	chunkSize = BigToHost32(buf);
	return SetChunkSize(chunkSize);
}