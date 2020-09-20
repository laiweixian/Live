#pragma once
#include "../Receive/BaseMessage.h"
#include "AMF/AMF.h"
#include "Command/CommandCall.h"
#include "Command/CommandClose.h"
#include "Command/CommandCloseStream.h"
#include "Command/CommandConnect.h"
#include "Command/CommandCreateStream.h"
#include "Command/CommandDeleteStream.h"
#include "Command/CommandPause.h"
#include "Command/CommandPlay.h"
#include "Command/CommandPlay2.h"
#include "Command/CommandPublish.h"
#include "Command/CommandReceiveAudio.h"
#include "Command/CommandSeek.h"
#include "Command/CommandReceiveVideo.h"


#define ERR_NO_AMF3				-1
#define ERR_AMF0_PARSE			-2
#define ERR_NO_COMMAND_NAME		-3
#define ERR_VALID_OBJECT		-4

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
					*RECEIVE_VIDEO_COMMAND = "receiveVideo",\
					*PUBLISH_COMMAND		=  "publish",\
					*SEEK_COMMAND			= "seek",\
					*PAUSE_COMMAND			= "pause";

enum CommandType
{
	NONE, 
	CONNECT, CALL,CLOSE,CLOSE_STREAM,CREATE_STREAM,
	PLAY, PLAY2, DELETE_STREAM, RECEIVE_AUDIO,RECEIVE_VIDEO, PUBLISH,SEEK, PAUSE
};


class CCommandMessage
{
protected:
	CCommandMessage();
	 ~CCommandMessage() ;
public:
	struct Object { CommandType cType; void* pCmdObj; };

	static Object* Decode(CBaseMessage* pMsg);
	static void FreeObject(Object** ppObj);



private:
	static uint8_t* TranslatePayload(CommandType cType, void *pCls,int *outLenght);


};

