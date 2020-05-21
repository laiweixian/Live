#pragma once

#include "../stdafx.h"

struct AudioElememt
{
	int sampleRate;
	int channels;
};

struct VideoElement
{
	int width ;
	int height;
};

class CMedia
{
public:
	CMedia(AudioElememt aEle, VideoElement vEle);
	~CMedia();

	int OpenMedia();
	int EncodeBMP(const AVFrame* rgb);
	int EncodePCM(const AVFrame* pcm);
	int CloseMedia();
	
	
	static AVFrame* MixVoice(AVFrame* pcm0,AVFrame* pcm1);
	static AVFrame* MixImage(AVFrame* bg,AVFrame* front,int x,int y);

	static AVFrame* YUV2BMP(AVFrame *yuv);
	static AVFrame* BMP2YUV(AVFrame *bgr);

private:

	int InitFormat();
	int InitAudioCode();
	int InitVideoCode();
	
private:
	AudioElememt m_AEle;
	VideoElement m_VEle;

	AVFormatContext *m_MP4;
	AVCodecContext *m_VideoCodec;
	AVCodecContext *m_AudioCodec;
};

