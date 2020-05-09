#include "H264Encode.h"

CH264Encode::CH264Encode() : m_FormatContext(NULL)
{
	
}

int CH264Encode::Init()
{
	const char *video = "my.mp4";
	int ret = 0;
	AVOutputFormat *pOutFormat = NULL;
	AVCodec *pVideo = NULL , *pAudio = NULL;

	ret = avformat_alloc_output_context2(&m_FormatContext, NULL, NULL, video);
	if (!(ret >= 0))
		return ret;
	
	pVideo = avcodec_find_encoder(AV_CODEC_ID_H264);
	pAudio = avcodec_find_encoder(AV_CODEC_ID_AAC);
	
	pOutFormat = m_FormatContext->oformat;
	if (pOutFormat->video_codec != AV_CODEC_ID_NONE)
	{
		
	}
	if (pOutFormat->audio_codec != AV_CODEC_ID_NONE)
	{

	}


}

CH264Encode::~CH264Encode()
{
	if (m_FormatContext)
	avformat_free_context(m_FormatContext);
	m_FormatContext = NULL;
}

int CH264Encode::Encode(FrameType fType, const char* buff, const int buffLen)
{

}