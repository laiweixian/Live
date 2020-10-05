#include "PlayVideoThread.h"

CPlayVideoThread::CPlayVideoThread(IMediaEvent* pEvent):\
						m_Thread(NULL),m_Event(pEvent),m_SwCtx(NULL),m_BGR24(NULL)
{

}

CPlayVideoThread::~CPlayVideoThread()
{
	if (m_Thread)
	{
		TerminateThread(m_Thread,0);
		CloseHandle(m_Thread);
		m_Thread = NULL;
	}
}

int CPlayVideoThread::Start()
{
	DWORD tid;
	if (m_Thread)
		return -1;
	m_Thread = CreateThread(NULL, 0, ThreadProc, this, 0, &tid);
	return 0;
}

DWORD  CPlayVideoThread::ThreadProc(LPVOID lpParameter)
{
	CPlayVideoThread* pt = (CPlayVideoThread*)lpParameter;
	pt->Run();
	pt->m_Thread = NULL;
	return 0;
}

void CPlayVideoThread::Run()
{
	bool locked = false ,eof = false;
	queue<AVFrame*>* pFrames = NULL;

	while (1)
	{
		locked = Lock();
		eof = EndOfFile();

		if (locked == false)
		{
			Sleep(100);
			continue;
		}

		PopVideoFreamQueue(&pFrames);
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

void CPlayVideoThread::PlayQueue(queue<AVFrame*>* &pFrames)
{
	const int count = pFrames->size();
	int i = 0;
	AVFrame* pRaw = NULL;

	for (i=0;i<count;i++)
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

void CPlayVideoThread::Play(AVFrame* raw)
{
	int ret = -1;

	if (m_SwCtx == NULL || m_BGR24 == NULL)
		InitBGR(raw);

	ret = sws_scale(m_SwCtx,\
		raw->data, raw->linesize, 0, raw->height, \
		m_BGR24->data, m_BGR24->linesize);

	m_Event->OnImage(m_BGR24);
}

void CPlayVideoThread::InitBGR(AVFrame* raw)
{
	m_BGR24 = av_frame_alloc();
	m_BGR24->width = raw->width;
	m_BGR24->height = raw->height;
	m_BGR24->format = AVPixelFormat::AV_PIX_FMT_BGR24;

	av_image_alloc(m_BGR24->data, m_BGR24->linesize, m_BGR24->width, m_BGR24->height, AV_PIX_FMT_BGR24, 1);

	m_SwCtx = sws_getContext(raw->width, raw->height, (AVPixelFormat)raw->format, \
		m_BGR24->width, m_BGR24->height, (AVPixelFormat)m_BGR24->format, SWS_BICUBIC, NULL, NULL, NULL);

	return;
}