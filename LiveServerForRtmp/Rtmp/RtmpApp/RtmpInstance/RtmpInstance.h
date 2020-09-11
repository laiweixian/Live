#pragma once

#include "stdafx.h"



#include "VideoCodec.h"
#include "AudioCodec.h"


#define ERR_ACTOR_EXIST			-1
#define ERR_AUDIENCE_REPEAT		-2
#define ERR_ACTOR_NO_MATCH		-3

class CRtmpInstance
{
public:
	CRtmpInstance(string name);
	~CRtmpInstance();
public:
	string m_Name;
};


