#pragma once
#include "../BaseMessage.h"

#include "Command/HandleCall.h"
#include "Command/HandleClose.h"
#include "Command/HandleCloseStream.h"
#include "Command/HandleCreateStream.h"
#include "Command/HandleConnect.h"
#include "Command/HandleDeleteStream.h"
#include "Command/HandlePlay.h"
#include "Command/HandlePlay2.h"
#include "Command/HandlePause.h"
#include "Command/HandlePublish.h"
#include "Command/HandleReceiveAudio.h"
#include "Command/HandleReceiveVideo.h"
#include "Command/HandleSeek.h"

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

class CHandleCommandMessage  :  public CHandleConnect,\
								public CHandleCall,\
								public CHandlePause,\
								public CHandlePublish,\
								public CHandleSeek,\
								public CHandleClose,\
								public CHandleCloseStream,\
								public CHandleCreateStream,\
								public CHandlePlay,\
								public CHandlePlay2,\
								public CHandleReceiveAudio,\
								public CHandleReceiveVideo,\
								public CHandleDeleteStream
{
protected:
	CHandleCommandMessage();
	virtual ~CHandleCommandMessage() ;

protected:
	virtual int Handle(CBaseMessage* pMsg) final;

};

