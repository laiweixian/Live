#include "DecodeFrame.h"

CDecodeFrame* Create(AVFormatContext* fmtCtx, AVMediaType mType)
{
	int ret = -1;
	int streamIndex = -1;
	AVStream *pSt = NULL;
	AVCodec* decode = NULL;
	AVCodecContext *pCtx = NULL;
	AVDictionary *pOpts = NULL;
	CDecodeFrame* frame = NULL;

	ret = av_find_best_stream(fmtCtx, mType, -1, -1, NULL, 0);
	if (ret < 0)
		goto fail;
	streamIndex = ret;

	//
	pSt = fmtCtx->streams[streamIndex];

	//
	decode = avcodec_find_decoder(pSt->codecpar->codec_id);
	if (decode == NULL)
		goto fail;

	pCtx = avcodec_alloc_context3(decode);
	if (pCtx == NULL)
		goto fail;

	ret = avcodec_parameters_to_context(pCtx, pSt->codecpar);
	if (ret < 0)
		goto fail;

	ret = avcodec_open2(pCtx, decode, NULL);
	if (ret < 0)
		goto fail;

	frame = new CDecodeFrame(streamIndex, pCtx);
	return frame;

fail:
	return NULL;
}


CDecodeFrame::CDecodeFrame(int streamIndex, AVCodecContext* decode):\
			m_StreamIndex(streamIndex),m_Decode(decode)
{

}

CDecodeFrame::~CDecodeFrame()
{
	avcodec_free_context(&m_Decode);
}



int CDecodeFrame::GetIndex()
{
	return m_StreamIndex;
}

AVFrame* CDecodeFrame::decode_pkt(AVCodecContext* codecCtx, AVPacket* pkt)
{
	int ret = -1;
	AVFrame* pFrame = NULL;

	pFrame = av_frame_alloc();
	ret = avcodec_send_packet(codecCtx, pkt);
	if (ret < 0)
		goto fail;

	while (ret >= 0)
	{
		ret = avcodec_receive_frame(codecCtx, pFrame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
		{
		}
		else if (ret < 0)
			goto fail;
		else
			break;
	}

	return pFrame;

fail:
	if (pFrame) av_frame_free(&pFrame);
	return NULL;
}

AVFrame*& CDecodeFrame::DecodePacket(AVPacket* pkt)
{
	AVFrame *raw = NULL;

	raw = decode_pkt(m_Decode, pkt);
	if (raw == NULL)
		return raw;

	if (raw->format == -1)
		return raw;
	return raw;
}

