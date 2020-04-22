#pragma once

#include "../../AMF/AMF.h"
#include "../BaseCommand.h"

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

class CConnectCommand
{
private:
	CConnectCommand() = default;
	~CConnectCommand() = default;

public:
	struct CommandObject
	{
		BaseCommand::DataString  app;
		BaseCommand::DataString  flashver;
		BaseCommand::DataString  swfUrl;
		BaseCommand::DataString  tcUrl;
		BaseCommand::DataBoolean fpad;
		BaseCommand::DataInt	 audioCodes;
		BaseCommand::DataInt	 videoCodes;
		BaseCommand::DataInt	 videoFunction;
		BaseCommand::DataString  pageUrl;
		BaseCommand::DataInt	 objectEncoding;
	};
	typedef BaseCommand::DataObject OptionalUserArguments;
	struct Context {
		string name;
		uint32_t transactionID;
		CommandObject obj;
		OptionalUserArguments optional;
	};

	static Context* Create(uint8_t* pData, uint32_t dataLen, AMFType aType);
	static void Content_free(Context** ppContent);
private:
	static Context* ParseAMF0(uint8_t* pData, uint32_t dataLen);
	static Context* ParseAMF3(uint8_t* pData, uint32_t dataLen);
};