#pragma once
#include "Rtmp/RtmpApp/RtmpMessage/BaseMessage.h"

#define ERR_NO_AMF3	-1
#define ERR_AMF0_PARSE	-2
#define ERR_NO_COMMAND_NAME -3
#define ERR_VALID_OBJECT	-4

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
	virtual int SetConnect(const char* rtmpurl) = 0;
	
private:
	int ConnectRespose();
	int CallRespose();
	int CloseRespose();
	int CreateStreamRespose();
	int PlayRespose();
	int Play2Respose();
	int DeleteStreamRespose();
	int CloseStreamRespose();
	int ReceiveAudioRespose();
	int ReceiveVideoRespose();
	int PublishRespose();
	int SeekRespose();
	int PauseRespose();
};

enum AudioCodes
{
	SUPPORT_SND_NONE = 0x0001,
	SUPPORT_SND_ADPCM = 0x0002,
	SUPPORT_SND_MP3 = 0x0004,
	SUPPORT_SND_INTEL = 0x0008,
	SUPPORT_SND_UNUSED = 0x0010,
	SUPPORT_SND,NELLY8 = 0x0020,
	SUPPORT_SND_NELLY = 0x0040,
	SUPPORT_SND_G711A = 0x0080,
	SUPPORT_SND_G711U = 0x0100,
	SUPPORT_SND_NELLY16 = 0x0200,
	SUPPORT_SND_AAC = 0x0400,
	SUPPORT_SND_SPEEX = 0x0800,
	SUPPORT_SND_ALL = 0x0fff,
};

enum VideoCodes
{
	SUPPORT_VID_UNUSED = 0x0001,
	SUPPORT_VID_JPEG = 0x0002,
	SUPPORT_VID_SORENSON = 0x0004,
	SUPPORT_VID_HOMEBREW = 0x0008,
	SUPPORT_VID_VP6 = 0x0010,
	SUPPORT_VID_VP6ALPHA = 0x0020,
	SUPPORT_VID_HOMEBREWV = 0x0040,
	SUPPORT_VID_H264 = 0x0080,
	SUPPORT_VID_ALL = 0x00ff
};

enum VideoFunction
{
	SUPPORT_VID_CLIENT_SEEK	= 1
};

enum ObjectEncode
{
	OE_AMF0 = 0,OE_AMF3 = 3	
};
