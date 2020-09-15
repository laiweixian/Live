#pragma once

#include "Receive/ReceiveChunk.h"
#include "ReceiveMessage.h"
#include "SendMessage.h"


class CChunks : public CReceiveChunk,
				public CReceiveMessage,
				public CSendMessage
{
protected:
	CChunks();
	virtual ~CChunks();

protected:
	int OnChunks(uint8_t* src, const int srcLength);


private:
	 int AbortMessageHandle(CAbortMessage::Object *pObj) ;
	 int SetChunkSizeHandle(CSetChunkSize::Object *pObj) ;
	 int SendMessage(CBaseMessage* pMsg);
	
};
