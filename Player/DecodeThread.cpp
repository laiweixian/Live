#include "stdafx.h"
#include "DecodeThread.h"




CDecodeThread::CDecodeThread(string path):m_Path(path),m_Fmt(NULL),\
										  m_Audio(NULL),m_Video(NULL),\
										  m_Thread(NULL), m_Percent(-1)
{
	Init();
}

CDecodeThread::~CDecodeThread()
{
	if (m_Fmt) delete m_Fmt; m_Fmt = NULL;
	if (m_Audio) delete m_Audio; m_Audio = NULL;
	if (m_Video) delete m_Video; m_Video = NULL;
	if (m_Thread)
	{
		TerminateThread(m_Thread, 0);
		CloseHandle(m_Thread);
		m_Thread = NULL;
	}
}

bool CDecodeThread::HaveVideo()
{
	return (m_Video != NULL);
}

bool CDecodeThread::HaveAudio()
{
	return (m_Audio != NULL);
}

bool CDecodeThread::EndOfFile()
{
	return (m_Thread == NULL);
}

int CDecodeThread::Seek(int percent)
{
	m_Percent = percent;
	return 0;
}

int CDecodeThread::Init()
{
	int ret = -1;

	m_Fmt = new CFormatContext(m_Path);
	ret = m_Fmt->Init();
	if (ret < 0)
		goto fail;

	m_Video = Create(m_Fmt->GetCtx(), AVMEDIA_TYPE_VIDEO);
	m_Audio = Create(m_Fmt->GetCtx(), AVMEDIA_TYPE_AUDIO);

	return 0;
fail:
	return ret;
}


int CDecodeThread::Start()
{
	DWORD tid;
	HANDLE hThread;

	if (m_Thread)
	{
		return 0;
	}

	hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &tid);
	m_Thread = hThread;
	return 0;
}

DWORD  CDecodeThread::ThreadProc(LPVOID lpParameter)
{
	CDecodeThread* pdt = (CDecodeThread*)lpParameter;
	pdt->Run();
	pdt->m_Thread = NULL;
	return 0;
}

void CDecodeThread::Run()
{
	int ret;
	AVPacket pkt;
	bool locked = false;
	AVFormatContext* fmt = m_Fmt->GetCtx();
	AVFrame* raw = NULL;
	const int aIdx = m_Audio->GetIndex(), vIdx = m_Video->GetIndex();

	av_init_packet(&pkt);
	while (true)
	{
		if (Full())
		{
			UnLock();
			Sleep(100);
			continue;
		}

		locked = Lock();
		if (locked == false)
		{
			Sleep(100);
			continue;
		}

		//Ìø×ª
		if (m_Percent != -1)
		{
			m_Percent = -1;
		}


		ret = av_read_frame(fmt, &pkt);
		if (!(ret >= 0))
		{
			UnLock();
			break;
		}
			

		if (pkt.stream_index == aIdx)
		{
			raw = m_Audio->DecodePacket(&pkt);
			if (raw->format != -1)
				PushAudioFrame(raw);
		}
		else if (pkt.stream_index == vIdx)
		{
			raw = m_Video->DecodePacket(&pkt);
			if (raw->format != -1)
				PushVideoFrame(raw);
		}
			

		raw = NULL;
		av_packet_unref(&pkt);
	}
}

uint64_t CDecodeThread::Duration()
{
	return 0;
}
