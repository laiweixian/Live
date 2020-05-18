#pragma once

#include "../stdafx.h"

class CMedia
{
public:
	CMedia();
	~CMedia();

	int Encode(HDC hdc,BITMAPFILEHEADER fileHeader,BITMAPINFOHEADER inforHeader,const char* buff,const int buffLen);
	
private:
	AVFrame* YUV2BMP(AVFrame *yuv);
	int Render(HDC hdc, AVFrame* rgb);
	int EncodeFrame(AVFrame* yuv);
private:
	AVFormatContext *m_MP4;
	AVCodecContext *m_H264;
	AVCodecContext *m_AAC;
};