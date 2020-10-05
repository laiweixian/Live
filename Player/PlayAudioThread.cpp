#include "PlayAudioThread.h"

CPlayAudioThread::CPlayAudioThread(IMediaEvent* pEvent):\
				m_Event(pEvent),m_Thread(NULL)
{

}

CPlayAudioThread::~CPlayAudioThread()
{

}

int CPlayAudioThread::Start()
{
	DWORD tid;
	HANDLE hThread;

	if (m_Thread)
		return -1;

	hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &tid);
	m_Thread = hThread;
	return 0;
}

DWORD  CPlayAudioThread::ThreadProc(LPVOID lpParameter)
{
	CPlayAudioThread* pt = (CPlayAudioThread*)lpParameter;
	pt->Run();
	pt->m_Thread = NULL;
	return 0;
}

void CPlayAudioThread::Run()
{
	bool locked = false, eof = false;
	queue<AVFrame*>* pFrames = NULL;

	while (true)
	{
		locked = Lock();
		eof = EndOfFile();

		if (locked == false)
		{
			Sleep(100);
			continue;
		}

		PopAudioFrameQueue(&pFrames);
		UnLock();

		
		if (pFrames == NULL && eof)
			break;

		if (pFrames == NULL)
		{
			Sleep(100);
			continue;
		}

		PlayQueue(pFrames);
	}
}

void CPlayAudioThread::PlayQueue(queue<AVFrame*>*& pFrames)
{
	const int count = pFrames->size();
	int i = 0;
	AVFrame* pRaw = NULL;

	for (i = 0; i < count; i++)
	{
		pRaw = pFrames->front();
		pFrames->pop();

		Play(pRaw);

		av_frame_free(&pRaw);

		Sleep(33);
	}

	delete pFrames;
	pFrames = NULL;
}

void CPlayAudioThread::Play(AVFrame* raw)
{
	if (m_Event == NULL)
		return;


	
}