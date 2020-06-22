#include "SetChunkSize.h"

CSetChunkSize::CSetChunkSize()
{

}

CSetChunkSize::~CSetChunkSize()
{

}

int CSetChunkSize::HandleSetChunkSize(CBaseMessage* pMsg)
{
	uint8_t buf[4] = {0};
	uint32_t chunkSize = 0;

	memcpy(buf,pMsg->GetData(),4);
	chunkSize = BigToHost32(buf);
	return SetChunkSize(chunkSize);
}