#pragma once


#include "../stdafx.h"
#include "tools.h"

typedef void (*PlayVideo)(void *ctx, AVFrame *pRGB);
typedef void (*PlayAudio)(void *ctx, AVFrame *pPCM);

struct PlayContext
{
	void *ctx;
	PlayVideo renderer;
	PlayAudio play;
};


class CPlayMedia
{
public:
	CPlayMedia(string url , PlayContext* play);
	~CPlayMedia();

public:
	struct VideoContext
	{
		AVCodecContext *decode;
		int streamIdx;
		AVFrame *raw;
		AVFrame *rgb;
		SwsContext *swsCtx;
	};

	struct AudioContext
	{
		AVCodecContext *decode;
		int streamIdx;
		AVFrame *raw;
		AVFrame *pcm;
		SwrContext *swrCtx;
	};

	void Play();
	
public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
private:
	int PlayMedia();
	void FlushVideo(AVFrame* image);
	void FlushAudio(AVFrame* sound);

private:
	void InitFormatCtx();
	void InitCodec();
	void InitVideoCtx();
	void InitAudioCtx();
	static int open_codec_context(AVFormatContext* fmtCtx, AVMediaType mType, int* outStreamIdx,AVCodecContext **outCodecCtx);
	static AVFrame* decode_pkt(AVCodecContext* codecCtx,AVPacket* pkt);

protected:
	string m_Url;
	PlayContext *m_PlayCtx;

	AVFormatContext *m_Format;
	VideoContext m_Video;
	AudioContext m_Audio;

};