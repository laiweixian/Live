#include "PlayMedia.h"

CPlayMedia::CPlayMedia(string url, PlayContext* play):
					  m_Url(url),m_PlayCtx(play),\
				      m_Format(NULL), m_Video({ 0 }), m_Audio{0}
{
	
}

CPlayMedia::~CPlayMedia()
{

}

void CPlayMedia::InitFormatCtx()
{
	AVFormatContext *fmt = NULL;
	int ret = -1;

	ret = avformat_open_input(&fmt, m_Url.data(), NULL, NULL);
	if (ret < 0)
		return;
	
	ret = avformat_find_stream_info(fmt, NULL);
	if (ret < 0)
		return;

	m_Format = fmt;
}

void CPlayMedia::InitCodec()
{
	int ret = -1;
	ret = open_codec_context(m_Format, AVMEDIA_TYPE_VIDEO,&(m_Video.streamIdx),&(m_Video.decode));
	if (ret == 0)
		InitVideoCtx();
	
	ret = open_codec_context(m_Format, AVMEDIA_TYPE_AUDIO, &(m_Audio.streamIdx), &(m_Audio.decode));
	if (ret == 0)
		InitAudioCtx();
}

void CPlayMedia::InitVideoCtx()
{
	int ret = -1;
	const int width = m_Video.decode->width, \
		height = m_Video.decode->height;

	m_Video.raw = av_frame_alloc();
	m_Video.rgb = av_frame_alloc();
	ret = av_image_alloc(m_Video.rgb->data, m_Video.rgb->linesize, \
		width, height, AVPixelFormat::AV_PIX_FMT_BGR24, 1);
	
	//
	m_Video.swsCtx = sws_getContext(width, height, m_Video.decode->pix_fmt,
									width, height, AV_PIX_FMT_BGR24,
									SWS_BILINEAR, NULL, NULL, NULL);
}
void CPlayMedia::InitAudioCtx()
{
	int ret = -1;
	const int channels = m_Audio.decode->channels,\
		sample_rate = m_Audio.decode->sample_rate;

	m_Audio.raw = av_frame_alloc();
	m_Audio.pcm = av_frame_alloc();
	ret = av_samples_alloc(m_Audio.pcm->data, m_Audio.pcm->linesize, channels, sample_rate, AVSampleFormat::AV_SAMPLE_FMT_S16, 0);
	if (ret < 0)
	{

	}
}

int CPlayMedia::open_codec_context(AVFormatContext* fmtCtx, AVMediaType mType, int* outStreamIdx, AVCodecContext **outCodecCtx)
{
	int ret = -1;
	AVStream *pSt = NULL;
	int streamIdx = -1;
	AVCodec *pDec = NULL;
	AVCodecContext *decCtx = NULL;
	AVDictionary *pOpts = NULL;


	ret = av_find_best_stream(fmtCtx, mType, -1, -1, NULL, 0);
	if (ret < 0)
		return ret;

	streamIdx = ret;
	pSt = fmtCtx->streams[streamIdx];
	
	pDec = avcodec_find_decoder(pSt->codecpar->codec_id);
	if (pDec == NULL)
		return -1;
	
	decCtx = avcodec_alloc_context3(pDec);
	if (decCtx == NULL)
		return -2;

	ret = avcodec_parameters_to_context(decCtx, pSt->codecpar);
	if (ret < 0)
		return -3;

	ret = avcodec_open2(decCtx, pDec, NULL);
	if (ret < 0)
		return -4;

	*outStreamIdx = streamIdx;
	*outCodecCtx = decCtx;
	return 0;
}



void CPlayMedia::Play()
{
	HANDLE hThread = NULL;
	DWORD tid;
	InitFormatCtx();
	InitCodec();
	hThread = CreateThread(NULL, 0, CPlayMedia::ThreadProc, this, 0, &tid);
	return;
}

DWORD CPlayMedia::ThreadProc(LPVOID lpParameter)
{
	CPlayMedia* play = (CPlayMedia*)lpParameter;
	play->PlayMedia();
	ExitThread(0);
}


int CPlayMedia::PlayMedia()
{
	int ret = 0;
	AVPacket pkt ;
	AVFormatContext *fmtCtx = m_Format;
	AVCodecContext *videoCtx = m_Video.decode;
	AVCodecContext *audioCtx = m_Audio.decode;
	AVFrame *vRaw = NULL, *aRaw = NULL;
	
	
	av_init_packet(&pkt);
	while ( (ret = av_read_frame(fmtCtx,&pkt)) >= 0)
	{
		if (pkt.stream_index == m_Audio.streamIdx)
		{
			aRaw = decode_pkt(audioCtx,&pkt);
			if (aRaw->format != -1)
				FlushAudio(aRaw);
			if (aRaw) av_frame_free(&aRaw);
		}
		else if (pkt.stream_index == m_Video.streamIdx)
		{
			vRaw = decode_pkt(videoCtx, &pkt);
			if (vRaw->format != -1)
			{
				
				
			}
				
			if (vRaw) av_frame_free(&vRaw);
			
		
		}
		else
		{

		}

		av_packet_unref(&pkt);
	}


	
	return 0;
}

AVFrame* CPlayMedia::decode_pkt(AVCodecContext* codecCtx, AVPacket* pkt)
{
	int ret = -1;
	AVFrame *pFrame = NULL;

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


void CPlayMedia::FlushVideo(AVFrame* image)
{
	
	/*
	int ret = 0;
	SwsContext* ctx = NULL;
	const int srcWidth = image->width, srcHeight = image->height;
	const int dstWidth = 898, dstHeight =524;
	AVFrame *bgr24 = NULL;
	const AVPixelFormat pfmt = AV_PIX_FMT_BGR24;

	ctx = sws_getContext(srcWidth, srcHeight, (AVPixelFormat)image->format, \
		dstWidth, dstHeight, pfmt, \
		SWS_BILINEAR, NULL, NULL, NULL);
	if (ctx == NULL)
		return;

	bgr24 = av_frame_alloc();
	bgr24->height = dstWidth;
	bgr24->width = dstHeight;
	bgr24->format = pfmt;

	ret = av_image_alloc(bgr24->data, bgr24->linesize,\
		dstWidth, dstHeight, pfmt,1);
	if (ret < 0)
		return;

	
	ret = sws_scale(ctx, \
		image->data, image->linesize, \
		0, dstHeight, bgr24->data, bgr24->linesize);
	


	av_freep(&(bgr24->data[0]));
	av_frame_free(&bgr24);
	sws_freeContext(ctx);
	*/

	m_PlayCtx->renderer(m_PlayCtx->ctx, image);
}

void CPlayMedia::FlushAudio(AVFrame* sound)
{

}