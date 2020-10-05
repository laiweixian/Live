#pragma once
#include "stdafx.h"

class CDecodeFrame
{
public:
	

	CDecodeFrame(int streamIndex, AVCodecContext* decode);
	virtual ~CDecodeFrame();

	AVFrame*& DecodePacket(AVPacket* pkt);
	int GetIndex();


private:
	static AVFrame* decode_pkt(AVCodecContext* codecCtx, AVPacket* pkt);
protected:
	int m_StreamIndex;
	AVCodecContext* m_Decode;
};
CDecodeFrame* Create(AVFormatContext* fmtCtx, AVMediaType mType);