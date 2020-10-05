#pragma once
#include "DecodeThread.h"
#include "PlayAudioThread.h"
#include "PlayVideoThread.h"

typedef queue<AVFrame*> RawFrames;

class CPlayContext :public CDecodeThread,\
				    public CPlayAudioThread,\
					public CPlayVideoThread
{
public:
	CPlayContext(string path,IMediaEvent *pEvent);
	~CPlayContext();

	void Play();
	void Stop();
	void Seek(int percent);
	void Pause();

private:
	 bool Lock() ;
	 bool PushAudioFrame(AVFrame* raw);
	 bool PushVideoFrame(AVFrame* raw);
	 bool PopAudioFrameQueue(RawFrames** ppFrame);
	 bool PopVideoFreamQueue(RawFrames** ppFrame);
	 bool Full();
	 bool UnLock();
	 bool EndOfFile();
private:
	int StartAllThread();

protected:
	RawFrames *m_AudioFrames;
	RawFrames *m_VideoFrames;
	HANDLE m_HMux;

};
