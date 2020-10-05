#pragma once

#include "stdafx.h"

typedef struct tagBmp
{
	uint8_t *bits;
	int size;
	int width;
	int height;
}BGR24;

typedef struct tagPCM
{
	uint8_t *bits;
	int size;
}PCM;


typedef void (*PlayVideo)(void* ctx, BGR24* pBmp);
typedef void (*PlayAudio)(void* ctx, PCM* pPcm);
typedef void (*PlaySubtitle)(void* ctx, AVFrame* raw);

typedef struct tagPlayContext
{
	void *ctx;
	PlayVideo pv;
	PlayAudio pa;
	PlaySubtitle ps;
}PlayContext,*PPlayContext;

class CPlayFile
{
protected:
	CPlayFile();
	~CPlayFile();
public:
	typedef vector<AVFrame*> Frames;

	struct MediaStream {
		AVCodecContext *decode;
		int streamIdx;
		Frames *pQueue;
		HANDLE mutex;

		
	};

	struct Convert
	{
		SwsContext *vCtx;
		BGR24 bgr;
		PCM   pcm;
	};

	struct MediaContext
	{
		MediaStream video;
		MediaStream audio;
		Convert vConvert;
	};
	

	enum State
	{
		S_NONE = -1,
		S_PLAY,S_PAUSE,S_STOP
	};

public:
	static CPlayFile* Create(string filepath, PlayContext *pctx);
	void Destory();

	void Play();
	void Pause();
	void Stop();
	void Seek(uint16_t percent);
protected:
	int Init(string filepath, PlayContext *pctx);
	int InitFormatCtx(string filepath);
	int InitAudioCtx();
	int InitVideoCtx();

	void Begin();
	static DWORD WINAPI DecodeProc(LPVOID lpParameter);
	static DWORD WINAPI PlayAudioProc(LPVOID lpParameter);
	static DWORD WINAPI PlayVideoProc(LPVOID lpParameter);

	void DecodeThread();
	int DecodeAudio(AVPacket* pkt);
	int DecodeVideo(AVPacket* pkt);
	bool FrameCacheFull();

	void PlayVideoThread();
	Frames* &ConsumeVideo();
	void PlaySequenceVideo(Frames* freams);
	void PlayBackVideo(AVFrame* raw);

	void PlayAudioThread();
	Frames* &ConsumeAudio();
	void PlaySequenceAudio(Frames* freams);
	void PlayBackAudio(AVFrame* raw);

	bool OpenDecodeMutex();
	bool CloseDecodeMutex();
	bool OpenAudioMutex();
	bool OpenVideoMutex();
	bool CloseAudiaMutex();
	bool CloseVideoMutex();

	static time_t GetTime();
	
private:
	string m_Path;
	PlayContext *m_Ctx;

	HANDLE m_HDecode;
	HANDLE m_HPlayAudio;
	HANDLE m_HPlayVideo;
	AVFormatContext *m_Fmt;
	MediaContext m_MediaCtx;
	State m_State;
};
