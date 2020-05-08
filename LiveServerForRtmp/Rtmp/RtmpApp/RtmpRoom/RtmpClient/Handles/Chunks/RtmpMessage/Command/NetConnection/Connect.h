#pragma once

#include "../../AMF/AMF.h"

enum AudioCodesType
{
	SUPPORT_SND_NONE = 0x0001,	SUPPORT_SND_ADPCM = 0x0002,
	SUPPORT_SND_MP3	= 0x0004,	SUPPORT_SND_INTEL = 0x0008,
	SUPPORT_SND_UNUSED = 0x0010,SUPPORT_SND_NELLY8 = 0x0020,
	SUPPORT_SND_NELLY = 0x0040,SUPPORT_SND_G711A = 0x0080,
	SUPPORT_SND_G711U = 0x0100,SUPPORT_SND_AAC = 0x0400,
	SUPPORT_SND_SPEEX = 0x0800,SUPPORT_SND_ALL = 0x0fff
};
enum VideoCodesType
{
	SUPPORT_VID_UNUSED	= 0x0001,SUPPORT_VID_JPEG	= 0x0002,
	SUPPORT_VID_SORENSON = 0x0004,SUPPORT_VID_HOMEBREW = 0x0008,
	SUPPORT_VID_VP6		= 0x0010,SUPPORT_VID_VP6ALPHA  = 0x0020,
	SUPPORT_VID_HOMEBREWV = 0x0040,SUPPORT_VID_H264	= 0x0080,
	SUPPORT_VID_ALL		= 0x00ff
};
enum VideoFunctionType{SUPPORT_VID_CLIENT_SEEK	= 1};
enum ObjectEncodingType{AMF0 = 0 , AMF3 = 3};

#define DECLARE_CONNECT_COMMAND	\
	struct CommandObject{\
		string app;\
		string flashver;\
		string swfUrl;\
		string tcUrl;\
		bool	fpad;\
		uint16_t audioCodes;\
		uint16_t videoCodes;\
		uint16_t videoFunction;\
		string pageUrl;\
		uint16_t objectEncoding;};\
	struct Content{\
	string commandName;\
	int transactionID;\
	CommandObject obj;};

class CConnectCmd
{
private:
	CConnectCmd() ;
	~CConnectCmd();
public:
	DECLARE_CONNECT_COMMAND
	
	static CConnectCmd* Create(uint8_t* pData, uint32_t dataLen, AMFType aType);
private:
	static Content* ParseAMF0(uint8_t* pData, uint32_t dataLen);
	static Content* ParseAMF3(uint8_t* pData, uint32_t dataLen);
public:
	Content *m_Content;
};