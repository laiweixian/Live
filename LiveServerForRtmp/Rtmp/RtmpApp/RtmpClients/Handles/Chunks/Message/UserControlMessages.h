#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

#define ERR_NO_EXIST_CONTROL	-1
#define SERVER_NO_RECEIVE		-2

class CUserControlMessages
{
protected:
	CUserControlMessages();
	virtual ~CUserControlMessages();
protected:
	virtual int HandleUserControlMessages(CBaseMessage* pMsg) final;
private:
	int HandleStreamBegin(uint8_t* data,int dataLen);
	int HandleStreamEOF(uint8_t* data, int dataLen);
	int HandleStreamDry(uint8_t* data, int dataLen);
	int HandleSetBufferLength(uint8_t* data, int dataLen);
	int HandleStreamIsRecorded(uint8_t* data, int dataLen);
	int HandlePingRequest(uint8_t* data, int dataLen);
	int HandlePingRespose(uint8_t* data, int dataLen);
protected:
};