#include "../stdafx.h"
#include "H264Encode.h"


CH264Encode::CH264Encode() : m_FormatContext(NULL)
{
	
	
	
}

CH264Encode::~CH264Encode()
{
	if (m_FormatContext)	avformat_free_context(m_FormatContext);
	m_FormatContext = NULL;


}

int CH264Encode::Encode(BITMAPFILEHEADER fileHeader, BITMAPINFOHEADER inforHeader, const char* buff, const int buffLen)
{
	int ret ;	

	//
	AVFrame* rgb = NULL;
	const int rgbWidth = inforHeader.biWidth , rgbHeight = inforHeader.biHeight;
	//
	AVFrame* yuv = NULL;
	const int yuvWidth = rgbWidth ,yuvHeigth = rgbHeight;
	//
	SwsContext *swsCtx = NULL;

	//check input bitmap width,height,bitCount
	if (inforHeader.biBitCount != 32)
		return -1;

	//setting rgb data struct
	rgb = av_frame_alloc();
	rgb->format = AVPixelFormat::AV_PIX_FMT_ABGR;
	rgb->width = rgbWidth;
	rgb->height = rgbHeight;
	ret = av_frame_get_buffer(rgb,0);
	if (ret != 0)
		goto fail;
	memcpy(rgb->data[0],buff,buffLen);

	//setting yuv data struct
	yuv = av_frame_alloc();
	yuv->format = AVPixelFormat::AV_PIX_FMT_YUV420P;
	yuv->width = yuvWidth;
	yuv->height = yuvHeigth;
	ret = av_frame_get_buffer(yuv,0);
	if (ret != 0)
		goto fail;
	
	//setting context
	swsCtx = sws_getContext(rgb->width,rgb->height, AVPixelFormat::AV_PIX_FMT_ABGR,\
							yuv->width,yuv->height, AVPixelFormat::AV_PIX_FMT_YUV420P,\
							SWS_BILINEAR,NULL,NULL,NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx,rgb->data,rgb->linesize,0,rgb->height,\
					yuv->data,yuv->linesize);
	

	YUV2BMP(yuv);
	return 0;

fail:
	return ret;
}

int CH264Encode::YUV2BMP(AVFrame *yuv)
{
	int ret ;
	AVFrame *bmp = NULL;
	SwsContext *swsCtx = NULL;
	CDialog *pShow;

	bmp = av_frame_alloc();
	bmp->format = AV_PIX_FMT_BGR24;
	bmp->width = (yuv->width);
	bmp->height = (yuv->height);
	ret = av_frame_get_buffer(bmp,0);
	if (ret != 0)
		goto fail;

	swsCtx = sws_getContext(yuv->width, yuv->height, AVPixelFormat::AV_PIX_FMT_YUV420P, \
		bmp->width, bmp->height, AV_PIX_FMT_BGR24, \
		SWS_BILINEAR, NULL, NULL, NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx, yuv->data, yuv->linesize, 0, yuv->height, \
		bmp->data, bmp->linesize);
	
	//

	pShow = new CDialog();
	pShow->Create(IDD_SHOW_BMP_DLG);
	pShow->ShowWindow(SW_SHOWNORMAL);
	
	Render(pShow->GetDC()->GetSafeHdc(),bmp);

	return 0;
fail:
	return ret;
}

int CH264Encode::Render(HDC hdc, AVFrame* rgb)
{
	
	HBITMAP hDDB;

	hDDB = CreateBitmap(rgb->width,rgb->height,1,24,rgb->data[0]);
	if (hDDB == NULL)
		goto fail;

	

fail:
	return -1;	
}