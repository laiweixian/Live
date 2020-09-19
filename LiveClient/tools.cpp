#include "tools.h"

AVFrame* YUV2BMP(AVFrame *yuv)
{
	int ret;
	AVFrame *bgr = NULL;
	SwsContext *swsCtx = NULL;

	bgr = av_frame_alloc();
	if (bgr == NULL)
		goto fail;

	bgr->format = AV_PIX_FMT_BGR24;
	bgr->width = (yuv->width);
	bgr->height = (yuv->height);
	ret = av_frame_get_buffer(bgr, 0);
	if (ret != 0)
		goto fail;

	swsCtx = sws_getContext(yuv->width, yuv->height, (AVPixelFormat)yuv->format, \
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

AVFrame* BMP2YUV(AVFrame *bgr)
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

int  RenderToDC(HDC hdc, AVFrame* bgr)
{
	const int dcWidth = ::GetDeviceCaps(hdc, HORZRES);
	const int dcHeight = ::GetDeviceCaps(hdc, VERTSIZE);
	const int channels = 3;



	
	return 0;
}