#include "VideoDecode.h"
 
CVideoDecode::CVideoDecode(const AVCodecID decodeid) : m_Decode(NULL),m_Parse(NULL),m_Packet(NULL)
{
	InitDecode(decodeid);
	m_Packet = av_packet_alloc();
}

CVideoDecode::~CVideoDecode()
{
	if (m_Decode) avcodec_free_context(&m_Decode);	m_Decode = NULL;
}

int CVideoDecode::InitDecode(const AVCodecID decodeid)
{
	AVCodec *pDecode = NULL; 
	AVCodecContext *ctx = NULL;
	int ret = -1;

	pDecode = avcodec_find_decoder(decodeid);
	if (pDecode == NULL)
		goto fail;
	
	ctx = avcodec_alloc_context3(pDecode);
	if (ctx == NULL)
		goto fail;

	ret = avcodec_open2(ctx,pDecode,NULL);
	if (ret < 0)
		goto fail;

	m_Decode = ctx;	
	m_Parse = av_parser_init(pDecode->id);
	return 0;
fail:
	return -1;
}

int CVideoDecode::Decode(char* packet, int packetSize)
{
	
	
	

	
	

	return -1;
}	