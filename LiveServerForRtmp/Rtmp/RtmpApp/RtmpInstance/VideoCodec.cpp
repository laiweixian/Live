#include "VideoCodec.h"

CVideoCodec::CVideoCodec(const AVCodecID video /* = AV_CODEC_ID_H264 */) :m_VideoDecode(NULL)
{	
	
}

CVideoCodec::~CVideoCodec()
{
	if (m_VideoDecode) avcodec_free_context(&m_VideoDecode);
	
}

int CVideoCodec::OpenCodec()
{
	if (m_VideoDecode)
		return OK;
	else 
		return FAILURE;
}



int CVideoCodec::InitDecode(const AVCodecID decodeid)
{
	AVCodec *encode = NULL;
	AVCodecContext *ctx = NULL;
	int ret = 0;

	encode = avcodec_find_decoder(decodeid);
	if (encode == NULL)
		goto failure;

	ctx = avcodec_alloc_context3(encode);
	if (ctx == NULL)
		goto failure;

	ret = avcodec_open2(ctx, encode, NULL);
	if (ret < 0)
		goto failure;

	m_VideoDecode = ctx;
	return 0;
failure:
	return -1;
}

int CVideoCodec::CheckEncodePacket(uint8_t* data, int dataSize)
{
	return -1;
}

