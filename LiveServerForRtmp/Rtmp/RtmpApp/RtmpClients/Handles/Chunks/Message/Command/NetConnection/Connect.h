#pragma once


//AudioCodes
static const uint16_t SUPPORT_SND_NONE = 0x0001;
static const uint16_t SUPPORT_SND_ADPCM = 0x0002;
static const uint16_t SUPPORT_SND_MP3 = 0x0004;
static const uint16_t SUPPORT_SND_INTEL = 0x0008;
static const uint16_t SUPPORT_SND_UNUSED = 0x0010;
static const uint16_t SUPPORT_SND_NELLY8 = 0x0020;
static const uint16_t SUPPORT_SND_NELLY = 0x0040;
static const uint16_t SUPPORT_SND_G711A = 0x0080;
static const uint16_t SUPPORT_SND_G711U = 0x0100;
static const uint16_t SUPPORT_SND_AAC = 0x0400;
static const uint16_t SUPPORT_SND_SPEEX = 0x0800;
static const uint16_t SUPPORT_SND_ALL = 0x0fff;

//VideoCodes
static const uint16_t SUPPORT_VID_UNUSED = 0x0001;
static const uint16_t SUPPORT_VID_JPEG = 0x0002;
static const uint16_t SUPPORT_VID_SORENSON = 0x0004;
static const uint16_t SUPPORT_VID_HOMEBREW = 0x0008;
static const uint16_t SUPPORT_VID_VP6 = 0x0010;
static const uint16_t SUPPORT_VID_VP6ALPHA = 0x0020;
static const uint16_t SUPPORT_VID_HOMEBREWV = 0x0040;
static const uint16_t SUPPORT_VID_H264 = 0x0080;
static const uint16_t SUPPORT_VID_ALL = 0x00ff;

//VideoFunction
static const uint16_t SUPPORT_VID_CLIENT_SEEK = 1;

//ObjectEncoding
static const uint16_t _AMF0 = 0;
static const uint16_t _AMF3 = 3;

//command name
static const char* COMMAND_NAME = "connect";

//transaction id
static const uint16_t TRANSACTION_ID = 1;

//command object
static const char* COMMAND_OBJECT_MEMBER_NAME[10] = {
	"app" ,"flashver" ,"swfUrl" ,
	"tcUrl","fpad","audioCodecs",
	"videoCodecs","videoFunction",
	"pageUrl" , "objectEncoding"
};

