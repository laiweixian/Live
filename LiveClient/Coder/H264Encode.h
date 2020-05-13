#pragma once

#include "../stdafx.h"

class CH264Encode
{
public:
	CH264Encode();
	~CH264Encode();

	int Encode(BITMAPFILEHEADER fileHeader,BITMAPINFOHEADER inforHeader,const char* colorBuff,const int buffLen);

private:
	AVFormatContext *m_FormatContext;
	AVFrame *m_Bitmap;
	AVFrame *m_YUV420P;
	SwsContext *m_SwsCtx;
};