#pragma once

#include "../../AMF/AMF0.h"
#include "../../AMF/AMF3.h"
#include "stdafx.h"

//Flag values for the audioCodecs property
enum AudioCodecs {
	SUPPORT_SND_NONE = 0x0001,
	SUPPORT_SND_ADPCM = 0x0002,
	SUPPORT_SND_MP3 = 0x0004,
	SUPPORT_SND_INTEL = 0x0008,
	SUPPORT_SND_UNUSED = 0x0010,
	SUPPORT_SND_NELLY8 = 0x0020,
	SUPPORT_SND_NELLY = 0x0040,
	SUPPORT_SND_G711A = 0x0080,
	SUPPORT_SND_G711U = 0x0100,
	SUPPORT_SND_NELLY16 = 0x0200,
	SUPPORT_SND_AAC = 0x0400,
	SUPPORT_SND_SPEEX = 0x0800,
	SUPPORT_SND_ALL = 0x0FFF,
};

//Flag values for the videoCodecs Property
enum VideoCodecs
{
	SUPPORT_VID_UNUSED = 0x0001,
	SUPPORT_VID_JPEG = 0x0002,
	SUPPORT_VID_SORENSON = 0x0004,
	SUPPORT_VID_HOMEBREW = 0x0008,
	SUPPORT_VID_VP6 = 0x0010,/*(On2)*/
	SUPPORT_VID_VP6ALPHA = 0x0020, /*On2 with alpha channel*/
	SUPPORT_VID_HOMEBREWV = 0x0040,/*screensharing v2*/
	SUPPORT_VID_H264 = 0x0080,
	SUPPORT_VID_ALL = 0x00FF
};

//Flag values for the videoFunction property
enum VideoFunction
{
	SUPPORT_VID_CLIENT_SEEK	= 1
};

//Values for the object encoding property
enum ObjectEncoding
{
	AMF0 = 0,
	AMF3 = 3
};

class CConnect
{
	
	
};
