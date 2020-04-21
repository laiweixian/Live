#pragma once

#include "../../AMF/AMF.h"

enum AudioCodes
{
	SUPPORT_SND_NONE  = 0x0001,
	SUPPORT_SND_ADPCM = 0x0002,
	SUPPORT_SND_MP3	  = 0x0004,
	SUPPORT_SND_INTEL = 0x0008,
	SUPPORT_SND_UNUSED = 0x0010,
	SUPPORT_SND_NELLY8	= 0x0020,
	SUPPORT_SND_NELLY	= 0x0040,
	SUPPORT_SND_G711A	= 0x0080,
	SUPPORT_SND_G711U	= 0x0100,
	SUPPORT_SND_AAC		= 0x0400,
	SUPPORT_SND_SPEEX   = 0x0800,
	SUPPORT_SND_ALL		= 0x0fff
};

enum VideoCodes
{
	SUPPORT_VID_UNUSED	= 0x0001,
	SUPPORT_VID_JPEG	= 0x0002,
	SUPPORT_VID_SORENSON = 0x0004,
	SUPPORT_VID_HOMEBREW = 0x0008,
	SUPPORT_VID_VP6		= 0x0010,
	SUPPORT_VID_VP6ALPHA  = 0x0020,
	SUPPORT_VID_HOMEBREWV = 0x0040,
	SUPPORT_VID_H264	= 0x0080,
	SUPPORT_VID_ALL		= 0x00ff
};

enum VideoFunction
{
	SUPPORT_VID_CLIENT_SEEK	= 1
};

enum ObjectEncoding
{
	AMF0 = 0 , AMF3 = 3
};


struct ConnObject
{
	string app;
	string flashver;
	string swfUrl;
	string tcUrl;
	bool fpad;
	uint16_t audioCodes;
	uint16_t videoCodes;
	uint16_t videoFunction;
	string pageUrl;
	uint16_t objectEncoding;
};

struct ConnOptiUserArgu
{
	
};

struct ConnCmd
{
	string name;
	uint32_t transactionID;
	ConnObject obj;
	ConnOptiUserArgu option;
};

void ConnCmd_Free(ConnCmd** ppCC);

class CConnectCommand
{
private:
	CConnectCommand(AMFType aType) ;
	~CConnectCommand() ;

	static ConnCmd* ParseAMF0(uint8_t* pData, uint32_t dataLen);
	static ConnCmd* ParseAMF3(uint8_t* pData, uint32_t dataLen);

public:
	static CConnectCommand* Create(uint8_t* pData, uint32_t dataLen, AMFType aType);

	void GenRespose();
private:
	AMFType m_AmfType;
	ConnCmd *m_ConnCmd;
};
