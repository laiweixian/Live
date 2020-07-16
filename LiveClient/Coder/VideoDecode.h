#pragma once

#include "stdafx.h"

class CVideoDecode
{
public:
	CVideoDecode(const AVCodecID decodeid);
	~CVideoDecode();

public:
	int Decode(char* packet,int packetSize);

private:
	int InitDecode(const AVCodecID decodeid);

private:
	AVCodecContext *m_Decode;
	AVCodecParserContext *m_Parse;
	AVPacket *m_Packet;
};
