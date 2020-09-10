#include "CommandMessage.h"

CCommandMessage::CCommandMessage()
{
	m_Obj = new CommandMessageObject;
	m_Obj->cType = CommandEnum::NONE;
	m_Obj->pObj = NULL;
}

CCommandMessage::~CCommandMessage()
{

}

int CCommandMessage::Handle(CBaseMessage* pMsg)
{
	CChunkHeader::Head header = pMsg->GetHead()->GetHead();
	AMF0::CParse* parse = NULL;
	AMF0::Data *pData = NULL;
	char commandName[1024] = {0};
	int ret = 0;
	void *cmdObj = NULL;
	CommandEnum cType = CommandEnum::NONE;

	if (header.messageTypeID == COMMAND_MESSAGE_TYPE_ID_AMF3)
		return ERR_NO_AMF3;

	parse = AMF0::CParse::Create(pMsg->GetData(),pMsg->GetDataLength());
	if (parse == NULL)
		return ERR_AMF0_PARSE;

	pData = parse->m_Datas.at(0);
	memcpy(commandName,pData->buf,pData->len);

	if (strcmp(commandName, CONNECT_COMMAND) == 0)
	{
		cType = CommandEnum::CONNECT;
		cmdObj = HandleConnect(parse);
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
		return -1;

	m_Obj->cType = cType;
	m_Obj->pObj = cmdObj;
	parse->Destroy();
	return CommandMessageHandle(m_Obj);
}

