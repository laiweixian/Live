#pragma once


#include "../stdafx.h"

class CPlayMedia
{
public:
	CPlayMedia(string mediaUrl, HDC showDc = NULL);
	~CPlayMedia();

public:
	void Display();

public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);


private:
	void Init();
	void Play();

protected:
	string m_Url;
	HDC m_Display;
	AVFormatContext *m_Format;
	AVCodecContext *m_DecodeVideo;
	AVCodecContext *m_DecodeAudio;

	int m_VideoStreamIndex;
	int m_AudioStreamIndex;

	
	

};