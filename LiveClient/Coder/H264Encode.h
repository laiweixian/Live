#pragma once

#include "../stdafx.h"

enum FrameType{NONE,RGB32,YUV420};

class CH264Encode
{
public:
	CH264Encode();
	~CH264Encode();

	int Init();
	int Encode(FrameType fType,const char* buff ,const int buffLen);
	int Stop() ;
private:
	AVFormatContext *m_FormatContext;

};