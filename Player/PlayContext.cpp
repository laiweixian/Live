#include "PlayContext.h"

#define DECODE_MUTEX "decode"
#define MAX_FRAME_NUM 20

CPlayContext::CPlayContext(string path,IMediaEvent *pEvent):\
							CDecodeThread(path),CPlayAudioThread(pEvent),CPlayVideoThread(pEvent),\
							m_VideoFrames(NULL),m_AudioFrames(NULL)
{
	

	m_HMux = CreateMutex(NULL, false, TEXT(DECODE_MUTEX));
}

CPlayContext::~CPlayContext()
{
	CloseHandle(m_HMux);

}

void CPlayContext::Play()
{
	StartAllThread();
}

void CPlayContext::Stop()
{

}

void CPlayContext::Seek(int percent)
{

}

void CPlayContext::Pause()
{

}

bool CPlayContext::Lock()
{
	HANDLE hMutex = NULL;

	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(DECODE_MUTEX));
	return (hMutex != NULL);
}

bool CPlayContext::UnLock()
{
	HANDLE hMutex = NULL;

	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(DECODE_MUTEX));
	if (hMutex == NULL)
		return false;

	return ReleaseMutex(hMutex);
}

bool CPlayContext::PushAudioFrame(AVFrame* raw)
{
	if (m_AudioFrames == NULL)
		m_AudioFrames = new RawFrames;

	m_AudioFrames->push(raw);
	return true;
}

bool CPlayContext::PushVideoFrame(AVFrame* raw)
{
	if (m_VideoFrames == NULL)
		m_VideoFrames = new RawFrames;
	

	m_VideoFrames->push(raw);
	return true;
}

bool CPlayContext::PopAudioFrameQueue(RawFrames** ppFrame)
{
	RawFrames* pFrames = m_AudioFrames;
	if (pFrames == NULL)
	{
		*ppFrame = NULL;
		return false;
	}

	m_AudioFrames = NULL;
	*ppFrame = pFrames;
	return NULL;
}

bool CPlayContext::PopVideoFreamQueue(RawFrames** ppFrame)
{
	RawFrames* pFrames = m_VideoFrames;
	if (pFrames == NULL)
	{
		*ppFrame = NULL;
		return false;
	}

	m_VideoFrames = NULL;
	*ppFrame = pFrames;
	return NULL;
}

bool CPlayContext::Full()
{
	bool fullA = false, fullV = false;
	
	if (m_AudioFrames == NULL)
		fullA = false;
	else
		fullA = m_AudioFrames->size() >= MAX_FRAME_NUM;

	if (m_VideoFrames == NULL)
		fullV = false;
	else
		fullV = m_VideoFrames->size() >= MAX_FRAME_NUM;

	return (fullA || fullV);
}

bool CPlayContext::EndOfFile()
{
	const bool  eof= CDecodeThread::EndOfFile();

	if (eof)
	{
		int i = 0;
		i = -1;
	}

	return eof;
}

int CPlayContext::StartAllThread()
{
	int ret = -1;

	ret = CDecodeThread::Start();
	if (HaveAudio())
		ret = CPlayAudioThread::Start();
	if (HaveVideo())
		ret = CPlayVideoThread::Start();
	return ret;
}