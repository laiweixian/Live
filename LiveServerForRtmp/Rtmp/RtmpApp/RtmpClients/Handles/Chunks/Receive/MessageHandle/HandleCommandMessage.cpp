#include "HandleCommandMessage.h"




CHandleCommandMessage::CHandleCommandMessage()
{

}

CHandleCommandMessage::~CHandleCommandMessage()
{

}

int CHandleCommandMessage::Handle(CBaseMessage* pMsg)
{
	CChunkHeader::Head header = pMsg->GetHead()->GetHead();
	AMF0::CParse * parse = NULL;
	AMF0::Data *pData = NULL;
	char commandName[1024] = {0};
	int ret = 0;

	if (header.messageTypeID == COMMAND_MESSAGE_TYPE_ID_AMF3)
		return ERR_NO_AMF3;

	parse = AMF0::CParse::Create(pMsg->GetData(),pMsg->GetDataLength());
	if (parse == NULL)
		return ERR_AMF0_PARSE;

	pData = parse->m_Datas.at(0);
	memcpy(commandName,pData->buf,pData->len);

	if (strcmp(commandName, CONNECT_COMMAND) == 0)
		ret = HandleConnect(parse);
	else if (strcmp(commandName, CALL_COMMAND) == 0)
		ret = HandleCall(parse);
	else if (strcmp(commandName, CLOSE_COMMAND) == 0)
		ret = HandleClose(parse);
	else if (strcmp(commandName, CREATE_STREAM_COMMAND) == 0)
		ret = HandleCreateStream(parse);
	else if (strcmp(commandName, PLAY_COMMAND) == 0)
		ret = HandlePlay(parse);
	else if (strcmp(commandName, PLAY2_COMMAND) == 0)
		ret = HandlePlay2(parse);
	else if (strcmp(commandName, DELETE_STREAM_COMMAND) == 0)
		ret = HandleDeleteStream(parse);
	else if (strcmp(commandName, CLOSE_STREAM_COMMAND) == 0)
		ret = HandleCloseStream(parse);
	else if (strcmp(commandName, RECEIVE_AUDIO_COMMAND) == 0)
		ret = HandleReceiveAudio(parse);
	else if (strcmp(commandName, RECEIVE_VIDEO_COMMAND) == 0)
		ret = HandleReceiveVideo(parse);
	else if (strcmp(commandName, PUBLISH_COMMAND) == 0)
		ret = HandlePublish(parse);
	else if (strcmp(commandName, SEEK_COMMAND) == 0)
		ret = HandleSeek(parse);
	else if (strcmp(commandName, PAUSE_COMMAND) == 0)
		ret = HandlePause(parse);
	else 
		ret = ERR_NO_COMMAND_NAME;

	parse->Destroy();
	return ret; 
}
