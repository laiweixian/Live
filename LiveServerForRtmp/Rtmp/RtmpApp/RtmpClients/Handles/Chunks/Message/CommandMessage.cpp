#include "CommandMessage.h"





CCommandMessage::CCommandMessage()
{

}

CCommandMessage::~CCommandMessage()
{

}

int CCommandMessage::HandleCommandMessage(CBaseMessage* pMsg)
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

int CCommandMessage::HandleConnect(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleCall(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleClose(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleCreateStream(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandlePlay(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandlePlay2(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleDeleteStream(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleCloseStream(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleReceiveAudio(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleReceiveVideo(AMF0::CParse *parse)
{	
	return -1;
}

int CCommandMessage::HandlePublish(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandleSeek(AMF0::CParse *parse)
{
	return -1;
}

int CCommandMessage::HandlePause(AMF0::CParse *parse)
{
	return -1;
}