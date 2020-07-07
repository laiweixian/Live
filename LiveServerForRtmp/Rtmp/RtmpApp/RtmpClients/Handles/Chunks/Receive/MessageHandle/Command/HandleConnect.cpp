#include "HandleConnect.h"

#define CONNECT_APP						"app"
#define CONNECT_FLASHVER				"flashver"
#define CONNECT_SWFURL					"swfUrl"
#define CONNECT_TCURL					"tcUrl"
#define CONNECT_FPAD					"fpad"
#define CONNECT_AUDIOCODECS				"audioCodecs"
#define CONNECT_VIDEOCODECS				"videoCodecs"
#define CONNECT_VIDEOFUNCTION			"videoFunction"
#define CONNECT_PAGEURL					"pageUrl"
#define CONNECT_OBJECTFUNCTION			"objectEncoding"

CHandleConnect::CHandleConnect()
{

}

CHandleConnect::~CHandleConnect()
{

}

int CHandleConnect::HandleConnect(AMF0::CParse *parse)
{
	char* rtmpUrl = NULL;
	int ret = 0;
	
	rtmpUrl = Analyze(parse);
	ret = SetConnectCommand(rtmpUrl);
	delete[] rtmpUrl; rtmpUrl = NULL;
	return ret;
}

char* CHandleConnect::Analyze(AMF0::CParse *parse)
{
	int ret = 0;
	AMF0::Data* pCommandObject = NULL;
	AMF0::UTF8 *pKey = NULL;
	AMF0::Data *pValue = NULL;
	char *url = NULL;

	pCommandObject = parse->m_Datas.at(2);
	pKey = AMF0::Convert(CONNECT_TCURL);
	pValue = AMF0::DataAlloc();
	ret = AMF0::CParse::MatchField(*pCommandObject, *pKey, *pValue);
	
	url = new char[pValue->len+1];	memset(url,0, pValue->len + 1);
	memcpy(url, pValue->buf, pValue->len);
	AMF0::Utf8Free(&pKey);
	AMF0::DataFree(&pValue);

	return url;
}
