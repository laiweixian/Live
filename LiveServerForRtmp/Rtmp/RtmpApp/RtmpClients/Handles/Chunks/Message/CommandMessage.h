#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

#define ERR_NO_AMF3	-1
#define ERR_AMF0_PARSE	-2
#define ERR_NO_COMMAND_NAME -3

static const char	*CONNECT_COMMAND = "connect",	\
					*CALL_COMMAND = "call",\
					*CLOSE_COMMAND = "close",\
					*CREATE_STREAM_COMMAND = "createStream",\
					*PLAY_COMMAND = "play",\
					*PLAY2_COMMAND = "play2",\
					\
					*DELETE_STREAM_COMMAND = "deleteStream",\
					*CLOSE_STREAM_COMMAND = "closeStream",\
					*RECEIVE_AUDIO_COMMAND = "receiveAudio",\
					*RECEIVE_VIDEO_COMMAND	= "receiveVideo",\
					*PUBLISH_COMMAND		=  "publish",\
					*SEEK_COMMAND			= "seek",\
					*PAUSE_COMMAND			= "pause";


class CCommandMessage
{
protected:
	CCommandMessage();
	virtual ~CCommandMessage() ;

protected:
	virtual int HandleCommandMessage(CBaseMessage* pMsg) final;

private:
	int HandleConnect(AMF0::CParse *parse);
	int HandleCall(AMF0::CParse *parse);
	int HandleClose(AMF0::CParse *parse);
	int HandleCreateStream(AMF0::CParse *parse);
	int HandlePlay(AMF0::CParse *parse);
	int HandlePlay2(AMF0::CParse *parse);
	int HandleDeleteStream(AMF0::CParse *parse);
	int HandleCloseStream(AMF0::CParse *parse);
	int HandleReceiveAudio(AMF0::CParse *parse);
	int HandleReceiveVideo(AMF0::CParse *parse);
	int HandlePublish(AMF0::CParse *parse);
	int HandleSeek(AMF0::CParse *parse);
	int HandlePause(AMF0::CParse *parse);

protected:
	virtual int SetConnectCmd(const char* app,const char* instance) = 0;

};
