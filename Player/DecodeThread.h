#pragma once

#include "stdafx.h"
#include "DecodeFrame.h"
#include "FormatContext.h"


class CDecodeThread
{
public:
	CDecodeThread(string path);
	virtual ~CDecodeThread();

protected:
	int Start(); 
	bool HaveVideo();
	bool HaveAudio();
	bool EndOfFile();
	int Seek(int percent);
	uint64_t Duration();// seconds

private:
	int Init();
private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void Run();
	virtual bool Lock() = 0;
	virtual bool Full() = 0;
	virtual bool UnLock() = 0;
	virtual bool PushAudioFrame(AVFrame* raw) = 0;
	virtual bool PushVideoFrame(AVFrame* raw) = 0;

private:
	string m_Path;
	CFormatContext *m_Fmt;
	CDecodeFrame *m_Audio;
	CDecodeFrame *m_Video;
	HANDLE m_Thread;
	int m_Percent;
};