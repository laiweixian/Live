#include "H264Encode.h"


CH264Encode::CH264Encode() : m_FormatContext(NULL), m_Bitmap(NULL),m_YUV420P(NULL), m_SwsCtx(NULL)
{
	int ret ;
	//
	const int srcWidth = 1920 , srcHeight = 1080;
	const AVPixelFormat srcFmt = AVPixelFormat::AV_PIX_FMT_ABGR;
	//
	const int dstWidth = 1920 , dstHeigth = 1080;
	const AVPixelFormat dstFmt = AVPixelFormat::AV_PIX_FMT_YUV420P;
	 
	m_SwsCtx = sws_getContext(srcWidth,srcHeight,srcFmt,\
							  dstWidth,dstHeigth,dstFmt,\
							  SWS_BILINEAR,NULL,NULL,NULL);
	
	avpicture_alloc()
}

CH264Encode::~CH264Encode()
{
	if (m_FormatContext)	avformat_free_context(m_FormatContext);
	m_FormatContext = NULL;
	if (m_YUV420P)	av_frame_free(&m_YUV420P);
	if (m_Bitmap) av_frame_free(&m_Bitmap);
	if (m_SwsCtx) sws_freeContext(m_SwsCtx);
	m_SwsCtx = NULL;
}

int CH264Encode::Encode(BITMAPFILEHEADER fileHeader, BITMAPINFOHEADER inforHeader, const char* colorBuff, const int buffLen)
{
	

	
	 
}