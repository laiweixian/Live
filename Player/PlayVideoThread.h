#pragma once

#include "stdafx.h"

#include "MediaEvent.h"
 

//消费者线程
class CPlayVideoThread
{
public:
	CPlayVideoThread(IMediaEvent* pEvent);
	virtual ~CPlayVideoThread();

	int Start();
private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void Run();
	void PlayQueue(queue<AVFrame*>* &pFrames);
	void Play(AVFrame* raw);
	void InitBGR(AVFrame* raw);
protected:
	virtual bool Lock() = 0;
	virtual bool PopVideoFreamQueue(queue<AVFrame*>** ppFrame) = 0;
	virtual bool UnLock() = 0;
	virtual bool EndOfFile() = 0;

private:
	IMediaEvent *m_Event;
	HANDLE m_Thread;

	SwsContext *m_SwCtx;
	AVFrame *m_BGR24;
};