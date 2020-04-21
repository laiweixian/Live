#pragma once

#include "stdafx.h"
#include "../AMF/AMF.h"

#include "NetConnection/Call.h"
#include "NetConnection/Close.h"
#include "NetConnection/Connect.h"
#include "NetConnection/CreateStream.h"

#include "NetStream/CloseStream.h"
#include "NetStream/DeleteStream.h"
#include "NetStream/Pause.h"
#include "NetStream/Play.h"
#include "NetStream/Play2.h"
#include "NetStream/Publish.h"
#include "NetStream/ReceiveAudio.h"
#include "NetStream/ReceiveVideo.h"
#include "NetStream/Seek.h"

enum CommandType
{
	NONE,

	//NetConnection
	CONNECT, CALL, CLOSE, CREATE_STREAM,	

	//NetStream
	PLAY, PLAY2, DELETE_STREAM, CLOSE_STREAM,
	RECEIVE_AUDIO, RECEIVE_VIDEO, PUBLISH,
	SEEK, PAUSE
};

struct Command
{
	CommandType cType;
	union 
	{
	

	};
};

class CCommands
{
public:
	CCommands();
	~CCommands();


};




