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
	
	static AVFrame* CaptureScreen(const HWND hwn = NULL,const int x = 0,const int y = 0, const int width = 0 , const int height = 0);			//output rgb from screen
	static AVFrame* CaptureCamera();			//output rgb from camera
	static AVFrame* CaptureLoudspeaker();		//output pcm from Loudspeaker
	static AVFrame* CaptureMicrophone();		//output pcm from Microphone
	static void EnumCamera();
	static void EnumMicrophone();
	static AVFrame* MixVoice(AVFrame* pcm0,AVFrame* pcm1);
	static AVFrame* MixImage(AVFrame* bg,AVFrame* front,int x,int y);

private:
	static AVFrame* Translate(HDC hdc,HBITMAP hBmp);
	static AVFrame* YUV2BMP(AVFrame *yuv);



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

