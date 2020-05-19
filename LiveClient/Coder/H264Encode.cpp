#include "../stdafx.h"
#include "H264Encode.h"

//format , video code , audio code
const char* FORMAT = ".mp4";
const AVCodecID VIDEO_CODE = AVCodecID::AV_CODEC_ID_H264;
const AVCodecID AUDIO_CODE = AVCodecID::AV_CODEC_ID_AAC;

CMedia::CMedia(): m_MP4(NULL), m_AudioCodec(NULL), m_VideoCodec(NULL)
{
	
	
	InitBegin();
	InitEnd();
}

int CMedia::InitBegin()
{
	int ret = 1;
	ret &= avformat_network_init();
	ret &= InitFormat();
	ret &= InitAudioCode();
	ret &= InitVideoCode();
	return ret;
}

int CMedia::InitEnd()
{
	return 0;
}

CMedia::~CMedia()
{
	if (m_MP4) avformat_free_context(m_MP4);
	m_MP4 = NULL;
	if (m_AudioCodec) avcodec_free_context(&m_AudioCodec);
	if (m_VideoCodec) avcodec_free_context(&m_VideoCodec);
}

int CMedia::Encode(HDC hdc,BITMAPFILEHEADER fileHeader, BITMAPINFOHEADER inforHeader, const char* buff, const int buffLen)
{
	return 0;
	int ret ;	
	//
	AVFrame* rgb = NULL;
	const int rgbWidth = inforHeader.biWidth , rgbHeight = inforHeader.biHeight;
	//
	AVFrame* yuv = NULL;
	const int yuvWidth = rgbWidth ,yuvHeigth = rgbHeight;
	//
	SwsContext *swsCtx = NULL;
	
	//setting rgb data struct
	rgb = av_frame_alloc();
	rgb->format = AVPixelFormat::AV_PIX_FMT_BGR24;
	rgb->width = rgbWidth;
	rgb->height = rgbHeight;
	ret = av_frame_get_buffer(rgb,0);
	if (ret != 0)
		goto fail;

	ret = av_image_fill_arrays(rgb->data,rgb->linesize,(unsigned char*)buff, (AVPixelFormat)rgb->format, rgb->width, rgb->height,24);
	//setting yuv data struct
	yuv = av_frame_alloc();
	yuv->format = AVPixelFormat::AV_PIX_FMT_YUV420P;
	yuv->width = yuvWidth;
	yuv->height = yuvHeigth;
	ret = av_frame_get_buffer(yuv,0);
	if (ret != 0)
		goto fail;
	
	//setting context
	swsCtx = sws_getContext(rgb->width,rgb->height, (AVPixelFormat)(rgb->format),\
							yuv->width,yuv->height, (AVPixelFormat)(yuv->format),\
							SWS_BILINEAR,NULL,NULL,NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx,rgb->data,rgb->linesize,0,rgb->height,\
					yuv->data,yuv->linesize);



	//
	av_frame_free(&rgb);		
	av_frame_free(&yuv);		
	sws_freeContext(swsCtx);
	

	return 0;

fail:
	return ret;
}

AVFrame* CMedia::YUV2BMP(AVFrame *yuv)
{
	return NULL;
	int ret ;
	AVFrame *bmp = NULL;
	SwsContext *swsCtx = NULL;
	
	bmp = av_frame_alloc();
	bmp->format = AV_PIX_FMT_BGR24;
	bmp->width = (yuv->width);
	bmp->height = (yuv->height);
	ret = av_frame_get_buffer(bmp,0);
	if (ret != 0)
		goto fail;

	swsCtx = sws_getContext(yuv->width, yuv->height,(AVPixelFormat) yuv->format, \
		bmp->width, bmp->height, (AVPixelFormat)bmp->format, \
		SWS_BILINEAR, NULL, NULL, NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx, yuv->data, yuv->linesize, 0, yuv->height, \
		bmp->data, bmp->linesize);

	return bmp;
fail:
	return NULL;
}

int CMedia::Render(HDC hdc, AVFrame* rgb)
{
	return 0;
	int ret ;
	HDC     hComDC;
	HBITMAP hBmp;
	BITMAPINFOHEADER infoHeader;
	HGDIOBJ hOld;
	BOOL result = FALSE;
	const int dcWidth = ::GetDeviceCaps(hdc, HORZRES);
	const int dcHeight = ::GetDeviceCaps(hdc, VERTRES);

	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biWidth = rgb->width;
	infoHeader.biHeight = rgb->height;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = ((infoHeader.biWidth* infoHeader.biBitCount + 23) / 24) * 3 * infoHeader.biHeight;
	infoHeader.biClrImportant = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;

	char *buff = new char[infoHeader.biSizeImage];
	memcpy(buff, rgb->data[0], infoHeader.biSizeImage);

	hComDC = GetDC(NULL);
	hBmp = CreateDIBitmap(hComDC,&infoHeader, CBM_INIT,buff,(BITMAPINFO*)&infoHeader, DIB_RGB_COLORS);
	SelectObject(hComDC,hBmp);
	
	result = ::StretchBlt(hdc,0,0,dcWidth,dcHeight, hComDC,0,0,rgb->width,rgb->height,SRCCOPY);

	DeleteObject(hBmp);
	ReleaseDC(NULL,hComDC);
	delete[] buff;
	return 0;
fail:
	return -1;	
}

int CMedia::EncodeFrame(AVFrame* yuv)
{
	return 0;
}

int CMedia::InitFormat()
{
	return 0;
}

int CMedia::InitAudioCode()
{
	AVCodec *aac = NULL;
	int i = 0;
	int ret = 0;
	
	aac = avcodec_find_encoder(AUDIO_CODE);
	if (aac == NULL)
	{
		PrintError("avcodec_find_encoder");
		return -1;
	}

	m_AudioCodec = avcodec_alloc_context3(aac);
	if (m_AudioCodec == NULL)
	{
		PrintError("avcodec_alloc_context3");
		return -1;
	}

	m_AudioCodec->sample_fmt = (aac->sample_fmts)[0];
	m_AudioCodec->sample_rate = 44100;
	m_AudioCodec->channels = 1;
	m_AudioCodec->bit_rate = 64000;


	ret = avcodec_open2(m_AudioCodec,aac,NULL);
	if (ret < 0)
	{
		PrintError("avcodec_open2");
		
		return -1;
	}
	

	/*
	vector<int> fors;
	i = 0;
	const int* ss = aac->supported_samplerates;
	while ((*(ss+i)))
	{
		fors.push_back(ss[i]);
		i++;
	}

	vector<AVSampleFormat> sfsv;
	i = 0;
	const AVSampleFormat *sfs = aac->sample_fmts;
	while (*(sfs+i))
	{
		sfsv.push_back(sfs[i]);
		i++;
	}
	*/

	

	
	return 0;
}

int CMedia::InitVideoCode()
{
	AVCodec *h264 = NULL;
	return 0;
}
