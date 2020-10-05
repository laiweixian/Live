#pragma once

#include "stdafx.h"
#include "MediaEvent.h"


class CPlayAudioThread
{
public:
	CPlayAudioThread(IMediaEvent* pEvent);
	virtual ~CPlayAudioThread();

	int Start();
	
private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void Run();
	void PlayQueue(queue<AVFrame*>*& pFrames);
	void Play(AVFrame* raw);
protected:
	virtual bool Lock() = 0;
	virtual bool PopAudioFrameQueue(queue<AVFrame*>** ppFrame) = 0;
	virtual bool UnLock() = 0;
	virtual bool EndOfFile() = 0;

private:
	IMediaEvent *m_Event;
	HANDLE m_Thread;

};