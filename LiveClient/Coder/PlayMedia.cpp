#include "PlayMedia.h"

CPlayMedia::CPlayMedia(string mediaUrl, HDC showDc ):\
				m_Url(mediaUrl),\
				m_Display(showDc), \
				m_Format(NULL),\
				m_DecodeAudio(NULL),\
				m_DecodeVideo(NULL),\
				m_VideoStreamIndex(-1),\
				m_AudioStreamIndex(-1)
{

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
	
	int i = 0;

	ret = avformat_open_input(&fmt, m_Url.data(), NULL, NULL);
	if (ret != 0)
		return;

	ret = avformat_find_stream_info(fmt,NULL);
	if (!(ret >= 0))
		return;
	
	//
	m_Format = fmt;
	for (i = 0; i < fmt->nb_streams; i++)
	{
		if (AVMEDIA_TYPE_VIDEO == fmt->streams[i]->codecpar->codec_type)	
			m_VideoStreamIndex = i;	
		else if (AVMEDIA_TYPE_AUDIO == fmt->streams[i]->codecpar->codec_type)
			m_AudioStreamIndex = i;	
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
	AVCodec *decodeVideo = NULL;
	AVCodecContext *ctx_codec = NULL;
	AVDictionary *pDict = NULL;

	decodeVideo = avcodec_find_decoder(AVCodecID::AV_CODEC_ID_H264);
	ctx_codec = avcodec_alloc_context3(decodeVideo);
	ret = avcodec_open2(ctx_codec, decodeVideo, &pDict);

	while (av_read_frame(ctx_format, pkt) >= 0) {
		if (pkt->stream_index == stream_idx) {
			
			ret = avcodec_send_packet(ctx_codec, pkt);
			if (ret < 0 || ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
				std::cout << "avcodec_send_packet: " << ret << std::endl;
				break;
			}
			while (ret >= 0) {
				ret = avcodec_receive_frame(ctx_codec, frame);
				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
					//std::cout << "avcodec_receive_frame: " << ret << std::endl;
					break;
				}
				std::cout << "frame: " << ctx_codec->frame_number << std::endl;
			}
		}
		av_packet_unref(pkt);
	}
	
}