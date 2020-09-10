#include "UserControlMessages.h"

CUserControlMessages::CUserControlMessages()
{

}

CUserControlMessages::~CUserControlMessages()
{

}

int CUserControlMessages::Handle(CBaseMessage* pMsg)
{
	CBaseMessage::Payload* payload = pMsg->GetPayload();
	const int length = payload->bufSize;
	const int dataFieldLen = length - 2;
	uint16_t eventType = 0;
	uint8_t *eventData = NULL;
	int ret = 0;
	
	eventType = BigToHost16(payload->buf);

	if (dataFieldLen > 0)
	{
		eventData = new uint8_t[dataFieldLen];
		memcpy(&eventType, payload->buf +2, dataFieldLen);
	}
		
	switch (eventType)
	{
	case 0:
		ret = HandleStreamBegin(eventData,dataFieldLen);
		break;
	case 1:
		ret = HandleStreamEOF(eventData,dataFieldLen);
		break;
	case 2:
		ret = HandleStreamDry(eventData,dataFieldLen);
		break;
	case 3:
		ret = HandleSetBufferLength(eventData,dataFieldLen);
		break;
	case 4:
		ret = HandleStreamIsRecorded(eventData,dataFieldLen);
		break;
	case 6:
		ret = HandlePingRequest(eventData,dataFieldLen);
		break;
	case 7:
		ret = HandlePingRespose(eventData,dataFieldLen);
		break;
	default:
		ret = ERR_NO_EXIST_CONTROL;
		break;
	}
	
	return ret;
}

int CUserControlMessages::HandleStreamBegin(uint8_t* data, int dataLen)
{
	//
	return SERVER_NO_RECEIVE;
}

int CUserControlMessages::HandleStreamEOF(uint8_t* data, int dataLen)
{
	return SERVER_NO_RECEIVE;
}

int CUserControlMessages::HandleStreamDry(uint8_t* data, int dataLen)
{
	return SERVER_NO_RECEIVE;
}

int CUserControlMessages::HandleSetBufferLength(uint8_t* data, int dataLen)
{
	return -1;
}

int CUserControlMessages::HandleStreamIsRecorded(uint8_t* data, int dataLen)
{
	return SERVER_NO_RECEIVE;
}

int CUserControlMessages::HandlePingRequest(uint8_t* data, int dataLen)
{
	return SERVER_NO_RECEIVE;
}

int CUserControlMessages::HandlePingRespose(uint8_t* data, int dataLen)
{
	return -1;
}