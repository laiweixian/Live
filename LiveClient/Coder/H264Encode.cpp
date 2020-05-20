#include "../stdafx.h"
#include "H264Encode.h"

//format , video code , audio code
const char* FORMAT = ".mp4";
const AVCodecID VIDEO_CODE = AVCodecID::AV_CODEC_ID_H264;
const AVCodecID AUDIO_CODE = AVCodecID::AV_CODEC_ID_AAC;

int Min(int a,int b)
{
	return (a>b?b:a);
}

int Max(int a, int b)
{
	return (a>b?a:b);
}

CMedia::CMedia(AudioElememt aEle, VideoElement vEle): m_AEle(aEle),m_VEle(vEle),m_MP4(NULL), m_AudioCodec(NULL), m_VideoCodec(NULL)
{
	
}

CMedia::~CMedia()
{
	if (m_MP4) avformat_free_context(m_MP4);
	m_MP4 = NULL;
	if (m_AudioCodec) avcodec_free_context(&m_AudioCodec);
	if (m_VideoCodec) avcodec_free_context(&m_VideoCodec);
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

int CMedia::InitFormat()
{
	AVFormatContext *fmtCtx = NULL ;
	AVIOContext *ioCtx = NULL;
	AVStream *videoStream = NULL, *audioStream = NULL; 

	const char *fileUrl = "G:\\1.mp4";
	int ret ; 

	if (m_AudioCodec == NULL || m_VideoCodec == NULL)	
		goto fail;

	ret = avformat_alloc_output_context2(&fmtCtx,NULL,NULL, fileUrl);
	if (ret < 0)
		goto fail;
	
	videoStream = avformat_new_stream(fmtCtx,m_VideoCodec->codec);
	audioStream = avformat_new_stream(fmtCtx,m_VideoCodec->codec);
	if (videoStream == NULL || audioStream == NULL)
		goto fail;
	
	ret = avio_open2(&(fmtCtx->pb), fileUrl, AVIO_FLAG_WRITE,NULL,NULL);
	if (ret <= 0)
		goto fail;
	m_MP4 = fmtCtx;
	return 0;
fail:
	avformat_free_context(fmtCtx);
	return -1;
}

int CMedia::InitAudioCode()
{
	AVCodec *aac = NULL;
	AVCodecContext *ctx = NULL;
	int ret = 0;
	
	aac = avcodec_find_encoder(AUDIO_CODE);
	if (aac == NULL)
		goto fail;
	
	ctx = avcodec_alloc_context3(aac);
	if (ctx == NULL)
		goto fail;

	ctx->sample_fmt = AV_SAMPLE_FMT_FLTP;
	ctx->sample_rate = 44100;
	ctx->channels = 1;
	ctx->channel_layout = AV_CH_LAYOUT_MONO;
	
	ret = avcodec_open2(ctx,aac,NULL);
	if (ret < 0)
		goto fail;
	
	m_AudioCodec = ctx;
	return 0;

fail:
	if (ctx) avcodec_free_context(&ctx);
	av_log(NULL,0,"InitAudioCode failure");
	return -1;
}

int CMedia::InitVideoCode()
{
	AVCodec *h264 = NULL;
	AVCodecContext *ctx = NULL;
	AVRational timeBase , frameRate;
	int ret ;

	h264 = avcodec_find_encoder(VIDEO_CODE);
	if (h264 == NULL)
		goto fail;

	ctx = avcodec_alloc_context3(h264);
	if (ctx == NULL)
		goto fail;

	timeBase.num = 1 ; timeBase.den = 25;
	frameRate.num = 25; frameRate.den = 1;

	ctx->pix_fmt = AVPixelFormat::AV_PIX_FMT_YUV420P;
	ctx->width = m_VEle.width;
	ctx->height = m_VEle.height;
	ctx->time_base = timeBase;
	ctx->framerate = frameRate;
//	ctx->gop_size = 10;
//	ctx->max_b_frames = 1;

	ret = avcodec_open2(ctx,h264,NULL);
	if (ret < 0)
		goto fail;
	m_VideoCodec = ctx;
	return 0;

fail:
	if (ctx) avcodec_free_context(&ctx);
	av_log(NULL,0,"InitVideoCode failure");
	return -1;
}


int CMedia::OpenMedia()
{
	int ret = 0;
	ret |= avformat_network_init();
	ret |= InitAudioCode();
	ret |= InitVideoCode();
	ret |= InitFormat();
	return ret;

fail:
	return ret ;
}

int CMedia::EncodeBMP(const AVFrame* rgb)
{
	return 0;
}

int CMedia::EncodePCM(const AVFrame* pcm)
{
	return 0;
}

int CMedia::CloseMedia()
{
	return 0;
}

AVFrame* CMedia::CaptureScreen(HWND hwn, const int x, const int y, const int width, const int height)			//output rgb from screen
{
	//
	AVFrame *bgr24 = NULL;
	HDC hdc = NULL ,hComDC = NULL;
	HBITMAP hBmp = NULL;
	HGDIOBJ hOld;
	int wndWidth = 0 , wndHeight = 0;
	int targetWidth = 0 , targetHeight = 0;
	
	hdc = GetDC(hwn);
	wndWidth = GetDeviceCaps(hdc, HORZRES); 
	wndHeight = ::GetDeviceCaps(hdc, VERTRES);

	targetWidth = width == 0 ? wndWidth:Min(width,wndWidth);
	targetHeight = height == 0 ? wndHeight:Min(height, wndHeight);
	hComDC = CreateCompatibleDC(hdc);
	hBmp = CreateCompatibleBitmap(hComDC, targetWidth, targetHeight);
	hOld = SelectObject(hComDC,hBmp);

	::StretchBlt(hComDC,0,0,targetWidth,targetHeight,hdc,x,y, targetWidth, targetHeight,SRCCOPY);
	
	bgr24 = Translate(hComDC,hBmp);

	ReleaseDC(hwn,hdc);
	DeleteDC(hComDC);
	DeleteObject(hBmp);

	return bgr24;
}

AVFrame* CMedia::CaptureCamera()			//output rgb from camera
{
	return NULL;
}

AVFrame* CMedia::CaptureLoudspeaker()		//output pcm from Loudspeaker
{
	return NULL;
}

AVFrame* CMedia::CaptureMicrophone()		//output pcm from Microphone
{
	return NULL;
}

void CMedia::EnumCamera()
{

}

void CMedia::EnumMicrophone()
{

}

AVFrame* CMedia::MixVoice(AVFrame* pcm0, AVFrame* pcm1)
{
	return NULL;
}

AVFrame* CMedia::MixImage(AVFrame* bg, AVFrame* front, int x, int y)
{
	return NULL;
}

AVFrame* CMedia::Translate(HDC hdc, HBITMAP hBmp)
{
	AVFrame *bgr24 = NULL;
	int ret ;
	BITMAP bitmap;
	BITMAPINFOHEADER infoHeader;
	DWORD bmpSize, DIBSize;
	char *buff = NULL;
	
	::GetObject(hBmp, sizeof(BITMAP), &bitmap);

	infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	infoHeader.biWidth = bitmap.bmWidth;
	infoHeader.biHeight = bitmap.bmHeight;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = BI_RGB;
	infoHeader.biSizeImage = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;

	bmpSize = ((infoHeader.biWidth * infoHeader.biBitCount + 23) / 24) * 3 * infoHeader.biHeight;
	buff = new char[bmpSize];
	GetDIBits(hdc, hBmp, 0, infoHeader.biHeight, buff, (BITMAPINFO*)&infoHeader, DIB_RGB_COLORS);

	bgr24 = av_frame_alloc();
	bgr24->format = AVPixelFormat::AV_PIX_FMT_BGR24;
	bgr24->width = infoHeader.biWidth;
	bgr24->height = infoHeader.biHeight;
	ret = av_frame_get_buffer(bgr24, 0);
	if (ret != 0)
		goto fail;

	ret = av_image_fill_arrays(bgr24->data, bgr24->linesize, (unsigned char*)buff, (AVPixelFormat)bgr24->format, bgr24->width, bgr24->height, 24);




	delete[] buff; buff = NULL;
	return bgr24;

fail:
	if (bgr24) av_frame_free(&bgr24);
	if (buff) delete[] buff; buff = NULL;
	return NULL;
}