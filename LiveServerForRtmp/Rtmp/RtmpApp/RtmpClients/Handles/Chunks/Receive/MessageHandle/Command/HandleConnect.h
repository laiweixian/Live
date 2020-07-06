#pragma once

#include "../AMF/AMF.h"
#include "Rtmp/RtmpApp/Message/RtmpMessage.h"

#define ERR_NOT_TC_URL	-1

class CHandleConnect
{
protected:
	CHandleConnect();
	virtual ~CHandleConnect();

protected:
	int HandleConnect(AMF0::CParse *parse);

protected:
	virtual int SetConnect(const char* rtmpurl, CRtmpMessage* response) = 0;
private:
	CRtmpMessage* CreateConnectResponse();
	char* CreateConnectCommand(int *outSize);
	char* CreateConnectTransaction(int *outSize);
	char* CreateConnectProperties(int *outSize);
	char* CreateConnectInformation(int *outSize);
};

enum AudioCodes
{
	SUPPORT_SND_NONE = 0x0001,
	SUPPORT_SND_ADPCM = 0x0002,
	SUPPORT_SND_MP3 = 0x0004,
	SUPPORT_SND_INTEL = 0x0008,
	SUPPORT_SND_UNUSED = 0x0010,
	SUPPORT_SND, NELLY8 = 0x0020,
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
	SUPPORT_VID_CLIENT_SEEK = 1
};

enum ObjectEncode
{
	OE_AMF0 = 0, OE_AMF3 = 3
};

