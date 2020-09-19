#include "PlayMedia.h"

CPlayMedia::CPlayMedia(string mediaUrl, HWND hwn):\
				m_Url(mediaUrl),\
				m_Display(hwn), \
				m_Format(NULL),\
				m_DecodeAudio(NULL),\
				m_DecodeVideo(NULL),\
				m_VideoFrame(NULL),
				m_AudioFrame(NULL),
				m_VideoStreamIndex(-1),\
				m_AudioStreamIndex(-1)
{
	av_register_all();
	const char* version = av_version_info();
	
	Init();
}

CPlayMedia::~CPlayMedia()
{

}

void CPlayMedia::Init()
{
	int ret = -1;
	AVFormatContext *fmt = NULL;
	AVCodec *decodeVideo = NULL, *decodeAudio = NULL;
	AVCodecContext *videoCtx = NULL, *audioCtx = NULL;
	AVDictionary *pDict = NULL;
	
	int i = 0;

	ret = avformat_open_input(&fmt, m_Url.data(), NULL, NULL);
	if (ret != 0)
		return;

	ret = avformat_find_stream_info(fmt,NULL);
	if (ret < 0)
		return;
	
	//
	m_Format = fmt;
	for (i = 0; i < fmt->nb_streams; i++)
	{
		if (AVMEDIA_TYPE_VIDEO == fmt->streams[i]->codecpar->codec_type)
		{
			decodeVideo = avcodec_find_decoder(fmt->streams[i]->codecpar->codec_id);
			
			videoCtx = avcodec_alloc_context3(decodeVideo);
			ret = avcodec_parameters_to_context(videoCtx, fmt->streams[i]->codecpar);
			if (ret == 0)
			{
				ret = avcodec_open2(videoCtx, decodeVideo, &pDict);
				if (ret == 0)
				{
					m_VideoStreamIndex = i;
					m_DecodeVideo = videoCtx;
				}
			}
		}
				
		else if (AVMEDIA_TYPE_AUDIO == fmt->streams[i]->codecpar->codec_type)
		{
			decodeAudio = avcodec_find_decoder(fmt->streams[i]->codecpar->codec_id);
			
			audioCtx = avcodec_alloc_context3(decodeAudio);
			ret = avcodec_parameters_to_context(audioCtx, fmt->streams[i]->codecpar);
			if (ret == 0)
			{
				ret = avcodec_open2(audioCtx, decodeAudio, &pDict);
				if (ret == 0)
				{
					m_AudioStreamIndex = i;
					m_DecodeAudio = audioCtx;
				}
			}
		}
			
	}
}

void CPlayMedia::Display()
{


	HANDLE hThread = NULL;
	DWORD tid;

	hThread = CreateThread(NULL, 0, CPlayMedia::ThreadProc, this, 0, &tid);
	
	return;
}

DWORD CPlayMedia::ThreadProc(LPVOID lpParameter)
{
	CPlayMedia* play = (CPlayMedia*)lpParameter;
	play->Play();
	ExitThread(0);
}

void CPlayMedia::Play()
{
	int ret;
	AVPacket *pkt = av_packet_alloc();;
	AVFrame *frame = av_frame_alloc();
	AVFormatContext* ctx_format = m_Format;
	int stream_idx = m_VideoStreamIndex;
	AVCodecContext *ctx_codec = m_DecodeVideo;


	struct dp {
		int64_t pts; int64_t dts;
	};
	dp item;
	vector<dp> dps;

	const int st = (1 / 25) * 1000;
	
	while (av_read_frame(ctx_format, pkt) >= 0) 
	{
		if (pkt->stream_index == stream_idx) 
		{
			ret = avcodec_send_packet(ctx_codec, pkt);
			if (ret < 0 || ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
				std::cout << "avcodec_send_packet: " << ret << std::endl;
				break;
			}

			while (ret >= 0)
			{
				ret = avcodec_receive_frame(ctx_codec, frame);
				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
					//std::cout << "avcodec_receive_frame: " << ret << std::endl;
					break;
				}
				
				Render(frame);
			}	

			Sleep(st);
			
			
		}
		av_packet_unref(pkt);
	}

}

void CPlayMedia::Render(AVFrame* yuv)
{
	AVFrame* bgr = YUV2BMP(yuv);
	if (bgr == NULL)
		return;

	HDC hdc = ::GetDC(m_Display);
	SetStretchBltMode(hdc, COLORONCOLOR);
	RenderToDC(hdc, bgr);
	::ReleaseDC(m_Display, hdc);
	av_frame_free(&bgr);
}