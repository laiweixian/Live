#include "FormatContext.h"

CFormatContext::CFormatContext(string path):m_Path(path),m_Ctx(NULL)
{

}

CFormatContext::~CFormatContext()
{

}

AVFormatContext* &CFormatContext::GetCtx()
{
	return m_Ctx;
}



int CFormatContext::Init()
{
	AVFormatContext* pCtx = NULL;
	int ret = -1;

	ret = avformat_open_input(&pCtx, m_Path.data(), NULL, NULL);
	if (ret < 0)
		goto fail;

	ret = avformat_find_stream_info(pCtx, NULL);
	if (ret < 0)
		goto fail;

	m_Ctx = pCtx;
	return 0;
fail:
	if (pCtx) avformat_free_context(pCtx);
	pCtx = NULL;
	return ret;
}