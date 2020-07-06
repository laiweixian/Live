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
	//the command obejct of connnect
	AMF0::Data* pCommandObject = NULL;
	AMF0::UTF8 *pKey = NULL;
	AMF0::Data *pValue = NULL;
	CRtmpMessage *pRespose = NULL;
	char url[2048] = { 0 };
	int ret = 0;

	pCommandObject = parse->m_Datas.at(2);
	pKey = AMF0::Convert(CONNECT_TCURL);
	pValue = AMF0::DataAlloc();
	ret = AMF0::CParse::MatchField(*pCommandObject, *pKey, *pValue);
	if (ret != 0)
		return ERR_NOT_TC_URL;

	memcpy(url, pValue->buf, pValue->len);
	AMF0::Utf8Free(&pKey);
	AMF0::DataFree(&pValue);

	pRespose = CreateResponse();

	ret = SetConnect(url, pRespose);
	return ret;
}

CRtmpMessage* CHandleConnect::CreateResponse()
{
	CRtmpMessage* pResponse = NULL;




	return NULL;
}

char* CHandleConnect::CreateCommandName(int *outSize)
{
	char* buf = NULL;
	int bufSize = 0;
	char *_result = "_result", *_error = "_error";

	buf = AMF0::CreateString(_result, strlen(_result), &bufSize);
	*outSize = bufSize;
	return buf;
}

char* CHandleConnect::CreateTransactionID(int *outSize)
{
	char* buf = NULL;
	int bufSize = 0;
	double tid = 1;

	buf = AMF0::CreateNumber(tid, &bufSize);
	*outSize = bufSize;
	return buf;
}

char* CHandleConnect::CreateProperties(int *outSize)
{
	char* buf = NULL;
	int bufSize = 0;

	return NULL;
}

char* CHandleConnect::CreateInformation(int *outSize)
{
	return NULL;
}