#pragma once

#include "stdafx.h"

#include "../Receive/BaseMessage.h"

class CSendChunk
{
protected:
	CSendChunk();
	virtual ~CSendChunk();

protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(uint8_t* src, const int srcLength) = 0;
private:
	
};