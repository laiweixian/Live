#pragma once

#include "stdafx.h"

class CVideoCodec
{
public:
	CVideoCodec(const AVCodecID video = AV_CODEC_ID_H264);
	~CVideoCodec();

public:
	int OpenCodec();
	int CheckEncodePacket(uint8_t* data,int dataSize);
	

private:

	int InitDecode(const AVCodecID decodeid);

private:
	AVCodecContext* m_VideoDecode;
	
};
