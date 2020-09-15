#include "CommandMessage.h"

CCommandMessage::CCommandMessage()
{

}

CCommandMessage::~CCommandMessage()
{

}



CCommandMessage::Object* CCommandMessage::Decode(CBaseMessage* pMsg)
{
	CCommandMessage::Object* pObj = NULL;
	CBaseMessage::Header head = pMsg->GetHeader();
	CBaseMessage::Payload payload = pMsg->GetPayload();
	AMF0::CParse* parse = NULL;
	AMF0::Data *pData = NULL;
	char commandName[1024] = { 0 };
	int ret = 0;
	CommandType cType;
	void *pCls = NULL;

	if (head.msgType == COMMAND_MESSAGE_TYPE_ID_AMF3)
		return NULL;

	parse = AMF0::CParse::Create(payload.buf, payload.bufSize);
	if (parse == NULL)
		return NULL;

	pData = parse->m_Datas.at(0);
	memcpy(commandName, pData->buf, pData->len);

	if (strcmp(commandName, CONNECT_COMMAND) == 0)
	{
		cType = CommandType::CONNECT;
		CCommandConnect *pCmd = new CCommandConnect;
		ret = pCmd->SetConnect(parse);
		pCls = pCmd;
	}
	else if (strcmp(commandName, CALL_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, CLOSE_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, CREATE_STREAM_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, PLAY_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, PLAY2_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, DELETE_STREAM_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, CLOSE_STREAM_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, RECEIVE_AUDIO_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, RECEIVE_VIDEO_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, PUBLISH_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, SEEK_COMMAND) == 0)
	{

	}
	else if (strcmp(commandName, PAUSE_COMMAND) == 0)
	{

	}
	else
		return NULL;

	parse->Destroy();

	pObj = new CCommandMessage::Object;
	pObj->cType = cType;
	pObj->pCommandObject = pCls;
	
	return pObj;
}

uint8_t* CCommandMessage::TranslatePayload(CommandType cType, void *pCls, int *outLength)
{
	uint8_t *buf = NULL;
	uint32_t length = 0;

	switch (cType)
	{
	case NONE:
		break;
	case CONNECT:
		
		break;
	case CALL:
		break;
	case CLOSE:
		break;
	case CLOSE_STREAM:
		break;
	case CREATE_STREAM:
		break;
	case PLAY:
		break;
	case PLAY2:
		break;
	case DELETE_STREAM:
		break;
	case RECEIVE_AUDIO:
		break;
	case RECEIVE_VIDEO:
		break;
	case PUBLISH:
		break;
	case SEEK:
		break;
	case PAUSE:
		break;
	default:
		break;
	}

	*outLength = length;
	return buf;
}

void CCommandMessage::FreeObject(Object** ppObj)
{
	return;
}

