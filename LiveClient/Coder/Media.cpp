#include "../stdafx.h"
#include "Media.h"

//format , video code , audio code
const char* FORMAT = ".mp4";
const AVCodecID VIDEO_CODE = AVCodecID::AV_CODEC_ID_H264;
const AVCodecID AUDIO_CODE = AVCodecID::AV_CODEC_ID_AAC;

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
	int ret ;
	AVFrame *bgr = NULL;
	SwsContext *swsCtx = NULL;
	
	bgr = av_frame_alloc();
	if (bgr == NULL)
		goto fail;

	bgr->format = AV_PIX_FMT_BGR24;
	bgr->width = (yuv->width);
	bgr->height = (yuv->height);
	ret = av_frame_get_buffer(bgr,0);
	if (ret != 0)
		goto fail;

	swsCtx = sws_getContext(yuv->width, yuv->height,(AVPixelFormat) yuv->format, \
		bgr->width, bgr->height, (AVPixelFormat)bgr->format, \
		SWS_BILINEAR, NULL, NULL, NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx, yuv->data, yuv->linesize, 0, yuv->height, \
		bgr->data, bgr->linesize);

	sws_freeContext(swsCtx);
	return bgr;
fail:
	if (bgr) av_frame_free(&bgr);
	if (swsCtx) sws_freeContext(swsCtx);
	return NULL;
}

AVFrame* CMedia::BMP2YUV(AVFrame *bgr)
{
	int ret;
	AVFrame *yuv = NULL;
	SwsContext *swsCtx = NULL;

	bgr = av_frame_alloc();
	if (bgr == NULL)
		goto fail;

	yuv->format = AV_PIX_FMT_YUV420P;
	yuv->width = (bgr->width);
	yuv->height = (bgr->height);
	ret = av_frame_get_buffer(yuv, 0);
	if (ret != 0)
		goto fail;

	swsCtx = sws_getContext(bgr->width, bgr->height, (AVPixelFormat)bgr->format, \
		yuv->width, yuv->height, (AVPixelFormat)yuv->format, \
		SWS_BILINEAR, NULL, NULL, NULL);
	if (swsCtx == NULL)
		goto fail;

	ret = sws_scale(swsCtx, bgr->data, bgr->linesize, 0, bgr->height, \
		yuv->data, yuv->linesize);

	sws_freeContext(swsCtx);
	return yuv;
fail:
	if (yuv) av_frame_free(&yuv);
	if (swsCtx) sws_freeContext(swsCtx);
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
	//
	static AVFrame* yuv = av_frame_alloc();


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


AVFrame* CMedia::MixVoice(AVFrame* pcm0, AVFrame* pcm1)
{
	return NULL;
}

AVFrame* CMedia::MixImage(AVFrame* bg, AVFrame* front, int x, int y)
{
	return NULL;
}
