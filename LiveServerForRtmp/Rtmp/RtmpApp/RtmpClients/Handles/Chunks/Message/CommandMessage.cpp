#include "CommandMessage.h"

#define CONNECT_APP						"app"
#define CONNECT_FLASHVER				"flashver"
#define CONNECT_SWFURL					"swfUrl"
#define CONNECT_TCURL					"tcUrl"
#define CONNECT_FPAD					"fpad"
#define CONNECT_AUDIOCODECS				"audioCodecs"
#define CONNECT_VIDEOCODECS				"videoCodecs"
#define CONNECT_VIDEOFUNCTION			"videoFunction"
#define CONNECT_PAGEURL					"pageUrl"
#define CONNECT_OBJECTFUNCTION			"objectEncoding"


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
	//the command obejct of connnect
	AMF0::Data* pCommandObject = NULL;
	AMF0::UTF8 *pKey = NULL;
	AMF0::Data *pValue = NULL;
	int ret = 0;

	pCommandObject = parse->m_Datas.at(2);
	
	pKey = AMF0::Convert(CONNECT_TCURL);
	pValue = AMF0::DataAlloc();
	ret = AMF0::CParse::MatchField(*pCommandObject,*pKey,*pValue);
	if (ret != 0)
		return ERR_VALID_OBJECT;

	ret = SetConnect(pKey->b)

	return SetConnect();
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

int CCommandMessage::ConnectRespose()
{
	return -1;
}

int CCommandMessage::CallRespose()
{
	return -1;
}

int CCommandMessage::CloseRespose()
{
	return -1;
}

int CCommandMessage::CreateStreamRespose()
{
	return -1;
}

int CCommandMessage::PlayRespose()
{
	return -1;
}

int CCommandMessage::Play2Respose()
{
	return -1;
}

int CCommandMessage::DeleteStreamRespose()
{
	return -1;
}

int CCommandMessage::CloseStreamRespose()
{
	return -1;
}

int CCommandMessage::ReceiveAudioRespose()
{
	return -1;
}

int CCommandMessage::ReceiveVideoRespose()
{
	return -1;
}

int CCommandMessage::PublishRespose()
{
	return -1;
}

int CCommandMessage::SeekRespose()
{
	return -1;
}

int CCommandMessage::PauseRespose()
{
	return -1;
}