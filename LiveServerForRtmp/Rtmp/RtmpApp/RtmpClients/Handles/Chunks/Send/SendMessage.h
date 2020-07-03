#pragma once

#include "stdafx.h"

class CSendMessage 
{
protected:
	CSendMessage();
	virtual ~CSendMessage();
protected:
	int Send2Message(uint8_t *buf,int bufSize);

protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(uint8_t* src, const int srcLength) = 0;
private:
	

};