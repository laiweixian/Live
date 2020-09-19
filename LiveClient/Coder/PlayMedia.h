#pragma once


#include "../stdafx.h"
#include "tools.h"

class CPlayMedia
{
public:
	CPlayMedia(string mediaUrl,HWND hwn);
	~CPlayMedia();

public:
	void Display();
	

public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);


private:
	void Init();
	void Play();
	void Render(AVFrame* yuv);

protected:
	string m_Url;
	HWND m_Display;
	AVFormatContext *m_Format;
	AVCodecContext *m_DecodeVideo;
	AVCodecContext *m_DecodeAudio;
	AVFrame *m_VideoFrame;
	AVFrame *m_AudioFrame;

	int m_VideoStreamIndex;
	int m_AudioStreamIndex;

	
	

};