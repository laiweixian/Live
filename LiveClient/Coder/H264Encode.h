#pragma once

#include "../stdafx.h"

class CH264Encode
{
public:
	CH264Encode();
	~CH264Encode();

	int Encode(BITMAPFILEHEADER fileHeader,BITMAPINFOHEADER inforHeader,const char* buff,const int buffLen);
	int YUV2BMP(AVFrame *yuv);
	int Render(HDC hdc,AVFrame* rgb);
private:
	AVFormatContext *m_FormatContext;
	
};