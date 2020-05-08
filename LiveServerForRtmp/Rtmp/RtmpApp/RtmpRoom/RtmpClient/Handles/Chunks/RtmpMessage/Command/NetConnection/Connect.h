#pragma once

#include "../../AMF/AMF.h"
namespace Connect
{
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
	static const uint16_t AMF0 = 0;
	static const uint16_t AMF3 = 3;

	//command name
	static const char* COMMAND_NAME = "connect";

	//transaction id
	static const uint16_t TRANSACTION_ID = 1;

	//command object
	static const char* APP	= "app";
	static const char* FLASHVER = "flashver";
	static const char* SWF_URL = "swfUrl";
	static const char* TC_URL = "tcUrl";
	static const char* FPAD = "fpad";
	static const char* AUDIO_CODECS = "audioCodecs";
	static const char* VIDEO_CODECS = "videoCodecs";
	static const char* VIDEO_FUNCTION = "videoFunction";
	static const char* PAGE_URL = "pageUrl";
	static const char* OBJECT_ENCODING = "objectEncoding";

	//optional user arguments


	struct Content;
	struct CommandObject;
	struct OptionalUserArguments;

	
	Content* ParseConnect(AMF0::CParse *pParse);
	Content* ParseConnect(AMF3::CParse *pParse);

	struct Content
	{
		string commandName;
		int transactionId;
		CommandObject cmdObj;
		OptionalUserArguments optUsrArg;
	};

	struct CommandObject
	{
		string app;
		string flashver;
		string swfUrl;
		string tcUrl;
		bool fpad;
		uint16_t audioCodecs;
		uint16_t videoCodecs;
		uint16_t videoFunction;
		string pageUrl;
		uint16_t objectEncoding;
	};

	struct OptionalUserArguments
	{

	};

};


