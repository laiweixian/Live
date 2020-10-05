#include "stdafx.h"
#include "PlayFile.h"

#define AUDIO_MUTEX	"audio_mutex"
#define VIDEO_MUTEX "video_mutex"

const int MAX_CACHE_FRAME = 20;

void DeletePCM(PCM** ppObj)
{
	PCM *pObj = *ppObj;
	if (pObj->bits) delete[] pObj->bits; 
	pObj->bits = NULL;

	delete (*ppObj);
	*ppObj = NULL;
}
void DeleteBGR24(BGR24** ppObj)
{
	BGR24 *pObj = *ppObj;
	if (pObj->bits) delete[] pObj->bits;
	pObj->bits = NULL;

	delete (*ppObj);
	*ppObj = NULL;
}

int open_codec_context(AVFormatContext* fmtCtx, AVMediaType mType, int* outStreamIdx, AVCodecContext **outCodecCtx)
{
	int ret = -1;
	AVStream *pSt = NULL;
	int streamIdx = -1;
	AVCodec *pDec = NULL;
	AVCodecContext *decCtx = NULL;
	AVDictionary *pOpts = NULL;

	ret = av_find_best_stream(fmtCtx, mType, -1, -1, NULL, 0);
	if (ret < 0)
		return ret;

	streamIdx = ret;
	pSt = fmtCtx->streams[streamIdx];

	pDec = avcodec_find_decoder(pSt->codecpar->codec_id);
	if (pDec == NULL)
		return -1;

	decCtx = avcodec_alloc_context3(pDec);
	if (decCtx == NULL)
		return -2;

	ret = avcodec_parameters_to_context(decCtx, pSt->codecpar);
	if (ret < 0)
		return -3;

	ret = avcodec_open2(decCtx, pDec, NULL);
	if (ret < 0)
		return -4;

	*outStreamIdx = streamIdx;
	*outCodecCtx = decCtx;
	return 0;
}

AVFrame* decode_pkt(AVCodecContext* codecCtx, AVPacket* pkt)
{
	int ret = -1;
	AVFrame *pFrame = NULL;

	pFrame = av_frame_alloc();
	ret = avcodec_send_packet(codecCtx, pkt);
	if (ret < 0)
		goto fail;
	while (ret >= 0)
	{
		ret = avcodec_receive_frame(codecCtx, pFrame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
		{
		}
		else if (ret < 0)
			goto fail;
		else
			break;
	}

	return pFrame;
fail:
	if (pFrame) av_frame_free(&pFrame);
	return NULL;
}

CPlayFile::CPlayFile() :m_Path(""), \
						m_Ctx(NULL), m_Fmt(NULL), m_MediaCtx({ 0 }),\
						m_State(S_NONE),\
	m_HPlayAudio(NULL),m_HDecode(NULL),m_HPlayVideo(NULL)
{

}

CPlayFile::~CPlayFile()
{
	if (m_HDecode) TerminateThread(m_HDecode,0);
	if (m_HPlayVideo)TerminateThread(m_HPlayVideo, 0);
	if (m_HPlayAudio)TerminateThread(m_HPlayAudio, 0);
	if (m_Fmt) avformat_free_context(m_Fmt);	
	if (m_MediaCtx.video.decode) avcodec_free_context(&m_MediaCtx.video.decode);
	if (m_MediaCtx.audio.decode) avcodec_free_context(&m_MediaCtx.audio.decode);
	if (m_MediaCtx.vConvert.vCtx) sws_freeContext(m_MediaCtx.vConvert.vCtx);

	
}

CPlayFile* CPlayFile::Create(string filepath, PlayContext *pctx)
{
	int ret = -1;
	CPlayFile *ppf = new CPlayFile;

	ret = ppf->Init(filepath, pctx);
	if (ret != 0)
	{
		ppf->Destory();
		ppf = NULL;
	}
		
	return ppf;
}

void CPlayFile::Destory()
{
	delete this;
}

void CPlayFile::Play()
{
	m_State = S_PLAY;
	if (m_Fmt)
		Begin();
}

void CPlayFile::Pause()
{
	m_State = S_PAUSE;
}

void CPlayFile::Stop()
{
	m_State = S_STOP;
}

void CPlayFile::Seek(uint16_t percent)
{
	
}

int CPlayFile::Init(string filepath, PlayContext *pctx)
{
	int ret = 0;
	ret = InitFormatCtx( filepath);
	if (ret != 0)
		return -1;
	
	ret = InitAudioCtx();
	if (ret != 0)
		return -1;

	ret = InitVideoCtx();
	if (ret != 0)
		return -1;
	
	m_Path = filepath;
	m_Ctx = pctx;
	return 0;
}

int CPlayFile::InitFormatCtx(string filepath)
{
	AVFormatContext *fmt = NULL;
	int ret = -1;

	ret = avformat_open_input(&fmt, filepath.data(), NULL, NULL);
	if (ret < 0)
		goto fail;

	ret = avformat_find_stream_info(fmt,NULL);
	if (ret < 0)
		goto fail;

	m_Fmt = fmt;
	return 0;
fail:
	if (fmt) avformat_close_input(&fmt);
	return -1;
}

int CPlayFile::InitAudioCtx()
{
	AVFormatContext *fmt = m_Fmt;
	int& streamIndex = m_MediaCtx.audio.streamIdx;
	AVCodecContext* &decode = m_MediaCtx.audio.decode;
	HANDLE mutex = NULL;
	int ret = -1;

	if (fmt == NULL)
		goto fail;

	ret = open_codec_context(fmt,AVMEDIA_TYPE_AUDIO,&streamIndex,&decode);
	if (ret != 0)
		goto fail;

	mutex = CreateMutex(NULL,false,TEXT(AUDIO_MUTEX));
	m_MediaCtx.audio.mutex = mutex;
	return 0;
fail:
	return -1;
}

int CPlayFile::InitVideoCtx()
{
	AVFormatContext *fmt = m_Fmt;
	int &streamIndex = m_MediaCtx.video.streamIdx;
	AVCodecContext* &decode = m_MediaCtx.video.decode;
	SwsContext *ctx = NULL;
	const AVPixelFormat pFmt = AV_PIX_FMT_BGR24;
	HANDLE mutex = NULL;
	int ret = -1;

	if (fmt == NULL)
		goto fail;

	ret = open_codec_context(fmt, AVMEDIA_TYPE_VIDEO, &streamIndex, &decode);
	if (ret != 0)
		goto fail;

	//
	ctx = sws_getContext(decode->width, decode->height, decode->pix_fmt, \
		decode->width, decode->height, pFmt, \
		SWS_BICUBIC, NULL, NULL, NULL);
	if (ctx == NULL)
		goto fail;

	m_MediaCtx.vConvert.vCtx = ctx;
	m_MediaCtx.vConvert.bgr.width = decode->width;
	m_MediaCtx.vConvert.bgr.height = decode->height;

	ret = av_image_get_buffer_size(AV_PIX_FMT_BGR24, decode->width,decode->height,1);
	m_MediaCtx.vConvert.bgr.size = ret;
	m_MediaCtx.vConvert.bgr.bits = new uint8_t[ret];
	

	mutex = CreateMutex(NULL, false, TEXT(VIDEO_MUTEX));
	m_MediaCtx.video.mutex = mutex;

	return 0;
fail:
	return -1;
}

void CPlayFile::Begin()
{
	DWORD tid;

	if (m_HDecode == NULL)
		m_HDecode = CreateThread(NULL, 0, CPlayFile::DecodeProc, this, 0, &tid);
	
	if (m_HPlayAudio == NULL)
		m_HPlayAudio = CreateThread(NULL, 0, CPlayFile::PlayAudioProc, this, 0, &tid);
	
	if (m_HPlayVideo == NULL)
		m_HPlayVideo = CreateThread(NULL, 0, CPlayFile::PlayVideoProc, this, 0, &tid);
}



DWORD  CPlayFile::DecodeProc(LPVOID lpParameter)
{
	CPlayFile *ppf = (CPlayFile*)lpParameter;
	ppf->DecodeThread();
	ExitThread(0);
	CloseHandle(ppf->m_HDecode);
	ppf->m_HDecode = NULL;
}

void CPlayFile::DecodeThread()
{
	AVPacket pkt = { 0 };
	AVFormatContext *fmtCtx = m_Fmt;
	int ret = -1;
	bool suspendMark = false;
	const HANDLE hCurTh = GetCurrentThread();
	const int vIndex = m_MediaCtx.video.streamIdx, \
		aIndex = m_MediaCtx.audio.streamIdx;

	int open_mutext = false;

	av_init_packet(&pkt);
	while (true)
	{
		if (FrameCacheFull() && open_mutext)
		{
			CloseDecodeMutex();
			Sleep(100);
			continue;
		}
		
		if (open_mutext == false)
		{
			open_mutext = OpenDecodeMutex();
			Sleep(100);
			continue;
		}
			

		ret = av_read_frame(fmtCtx, &pkt);
		if (!(ret >= 0))
			break;

		if (pkt.stream_index == vIndex)
			ret = DecodeVideo(&pkt);
		else if (pkt.stream_index == aIndex)
			ret = DecodeAudio(&pkt);
		else
			ret = 0;
		av_packet_unref(&pkt);
	}
}

bool CPlayFile::OpenDecodeMutex()
{
	const bool openv = OpenVideoMutex();
	const bool opena = OpenVideoMutex();

	return (openv && opena);
}

bool CPlayFile::CloseDecodeMutex()
{
	if (OpenDecodeMutex())
		return (CloseAudiaMutex() && CloseVideoMutex());
	else
		return false;
	
}

bool CPlayFile::OpenAudioMutex()
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(AUDIO_MUTEX));
	return (hMutex != NULL);
}

bool CPlayFile::OpenVideoMutex()
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(VIDEO_MUTEX));
	return (hMutex != NULL);
}

bool CPlayFile::CloseAudiaMutex()
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(AUDIO_MUTEX));
	if (hMutex == NULL)
		return false;
	return ReleaseMutex(hMutex);
}

bool CPlayFile::CloseVideoMutex()
{
	HANDLE hMutex = NULL;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, TEXT(VIDEO_MUTEX));
	if (hMutex == NULL)
		return false;
	return ReleaseMutex(hMutex);
}



int CPlayFile::DecodeAudio(AVPacket* pkt)
{
	AVCodecContext* decode = m_MediaCtx.audio.decode;
	AVFrame* pf = NULL;

	pf = decode_pkt(decode, pkt);
	if (pf == NULL)
		return -1;

	if (pf->format == -1)
		return 0;

	if (m_MediaCtx.audio.pQueue == NULL)
		m_MediaCtx.audio.pQueue = new Frames;

	m_MediaCtx.audio.pQueue->push_back(pf);
	return 0;
}

int CPlayFile::DecodeVideo(AVPacket* pkt)
{
	AVCodecContext* decode = m_MediaCtx.video.decode;
	AVFrame* pf = NULL;

	pf = decode_pkt(decode, pkt);
	if (pf == NULL)
		return -1;

	if (pf->format == -1)
		return 0;

	if (m_MediaCtx.video.pQueue == NULL)
		m_MediaCtx.video.pQueue = new Frames;

	m_MediaCtx.video.pQueue->push_back(pf);
	return 0;
}


DWORD  CPlayFile::PlayAudioProc(LPVOID lpParameter)
{
	CPlayFile *ppf = (CPlayFile*)lpParameter;
	ppf->PlayAudioThread();
	ExitThread(0);
	CloseHandle(ppf->m_HPlayAudio);
	ppf->m_HPlayAudio = NULL;
}

DWORD  CPlayFile::PlayVideoProc(LPVOID lpParameter)
{
	CPlayFile *ppf = (CPlayFile*)lpParameter;
	ppf->PlayVideoThread();
	ExitThread(0);
	CloseHandle(ppf->m_HPlayVideo);
	ppf->m_HPlayVideo = NULL;
}


void CPlayFile::PlayBackVideo(AVFrame* raw)
{
	return;
	int ret = -1;
	SwsContext *ctx = m_MediaCtx.vConvert.vCtx;
	
	uint8_t* data[4] = { 0 };
	int linesize[4] = {0};
	BGR24 * bgr24 = &m_MediaCtx.vConvert.bgr;

	
	ret = av_image_alloc(data, linesize, \
		bgr24->width, bgr24->height, AV_PIX_FMT_BGR24, 1);
	ret = sws_scale(ctx, \
		raw->data, raw->linesize, \
		0, bgr24->height, data, linesize);

	memcpy(bgr24->bits,data[0], bgr24->size);

	av_freep(&(data[0]));
	m_Ctx->pv(m_Ctx->ctx, bgr24);
}

void CPlayFile::PlayBackAudio(AVFrame* raw)
{
	
}

bool CPlayFile::FrameCacheFull()
{
	bool fullA = false ,fullV = false;
	if (m_MediaCtx.audio.pQueue)
	{
		if (m_MediaCtx.audio.pQueue->size() >= MAX_CACHE_FRAME)
			fullA = true;
		else
			fullA = false;
	}
	else
		fullA = false;

	if (m_MediaCtx.video.pQueue)
	{
		if (m_MediaCtx.video.pQueue->size() >= MAX_CACHE_FRAME)
			fullV = true;
		else
			fullV = false;
	}
	else
		fullV = false;

	return (fullA || fullV);
}


void CPlayFile::PlayVideoThread()
{
	Frames *frame = NULL;
	while (true)
	{
		frame = ConsumeVideo();
		if (frame == NULL && m_HDecode == NULL)
			break;	
		if (frame == NULL)
		{
			Sleep(1000);
			continue;
		}

		PlaySequenceVideo(frame);
		
		delete frame;
		frame = NULL;
	}
}


CPlayFile::Frames* &CPlayFile::ConsumeVideo()
{
	bool openMutex = false;
	Frames* fs = NULL;

	openMutex = OpenVideoMutex();
	if (openMutex == false)
		return fs;

	fs =  m_MediaCtx.video.pQueue;
	m_MediaCtx.video.pQueue = NULL;

	CloseVideoMutex();
	return fs;
}

void CPlayFile::PlaySequenceVideo(Frames* freams)
{
	auto it = freams->begin();
	AVFrame* f = NULL;

	for (it = freams->begin(); it != freams->end(); it++)
	{
		f = *it;
		PlayBackVideo(f);
		av_frame_free(&f);
		*it = NULL;

		Sleep(100);
	}
}

void CPlayFile::PlayAudioThread()
{
	Frames *frame = NULL;
	while (true)
	{
		frame = ConsumeAudio();
		if (frame == NULL && m_HDecode == NULL)
			break;
		if (frame == NULL)
		{
			Sleep(1000);
			continue;
		}

		PlaySequenceAudio(frame);

		frame->clear();
		delete frame;
		frame = NULL;
	}
}

CPlayFile::Frames* &CPlayFile::ConsumeAudio()
{
	bool openMutex = false;
	Frames* fs = NULL;

	openMutex = OpenAudioMutex();
	if (openMutex == false)
		return fs;

	fs = m_MediaCtx.audio.pQueue;
	m_MediaCtx.audio.pQueue = NULL;

	CloseAudiaMutex();
	return fs;
}

void CPlayFile::PlaySequenceAudio(Frames* freams)
{
	auto it = freams->begin();
	AVFrame* f = NULL;

	for (it = freams->begin(); it != freams->end(); it++)
	{
		f = *it;
		av_frame_free(&f);
		*it = NULL;
	}
}

time_t CPlayFile::GetTime()
{
	time_t t;

	t = time(NULL);
	return t;
}





