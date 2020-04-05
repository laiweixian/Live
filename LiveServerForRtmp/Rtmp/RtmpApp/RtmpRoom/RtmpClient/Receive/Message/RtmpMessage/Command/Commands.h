#pragma once

#include "stdafx.h"
#include "Call.h"
#include "Close.h"
#include "CloseStream.h"
#include "Connect.h"
#include "CreateStream.h"
#include "DeleteStream.h"
#include "Pause.h"
#include "Play.h"
#include "Play2.h"
#include "Publish.h"
#include "ReceiveAudio.h"
#include "ReceiveVideo.h"
#include "Seek.h"

enum CommandType
{
	//NetConnection
	CONNECT, CALL, CLOSE, CREATE_STREAM,	

	//NetStream
	PLAY, PLAY2, DELETE_STREAM, CLOSE_STREAM,
	RECEIVE_AUDIO, RECEIVE_VIDEO, PUBLISH,
	SEEK, PAUSE
};




