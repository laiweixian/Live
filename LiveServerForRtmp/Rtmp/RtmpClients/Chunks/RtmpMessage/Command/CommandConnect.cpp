#include "stdafx.h"
#include "CommandConnect.h"


CCommandConnect::CCommandConnect():m_Obj(NULL)
{
}


CCommandConnect::~CCommandConnect()
{
}

int CCommandConnect::SetConnect(AMF0::CParse *parse)
{
	AMF0::Data* pCommandObject = NULL;
	CCommandConnect::Object *pObj = NULL;

	pCommandObject = parse->m_Datas.at(2);
	
	pObj = new CCommandConnect::Object;
	memset(pObj, 0, sizeof(CCommandConnect::Object));

	SetObject(pCommandObject, CONNECT_APP,pObj, CCommandConnect::SetApp);
	SetObject(pCommandObject, CONNECT_FLASHVER, pObj, CCommandConnect::SetFlashver);
	SetObject(pCommandObject, CONNECT_SWFURL, pObj, CCommandConnect::SetSwfUrl);
	SetObject(pCommandObject, CONNECT_TCURL, pObj, CCommandConnect::SetTcUrl);
	SetObject(pCommandObject, CONNECT_FPAD, pObj, CCommandConnect::SetFpad);
	SetObject(pCommandObject, CONNECT_AUDIOCODECS, pObj, CCommandConnect::SetAudioCodecs);
	SetObject(pCommandObject, CONNECT_VIDEOCODECS, pObj, CCommandConnect::SetVideoCodecs);
	SetObject(pCommandObject, CONNECT_VIDEOFUNCTION, pObj, CCommandConnect::SetVideoFunction);
	SetObject(pCommandObject, CONNECT_PAGEURL, pObj, CCommandConnect::SetPageUrl);
	SetObject(pCommandObject, CONNECT_OBJECTFUNCTION, pObj, CCommandConnect::SetObjectEncoding);

	m_Obj = pObj;
	return 0;
}

int CCommandConnect::SetObject(AMF0::Data* pData, const char* key, CCommandConnect::Object *pObj,SetValue sVal)
{
	int ret = 0;
	AMF0::UTF8 *pKey = NULL;
	AMF0::Data *pValue = NULL;
	char *val = NULL;

	pKey = AMF0::Convert(key);
	pValue = AMF0::DataAlloc();

	ret = AMF0::CParse::MatchField(*pData, *pKey, *pValue);
	if (ret == 0 && (pValue->len > 0) && (pValue->buf != NULL))
	{
		sVal(pObj,pValue);
	}

	AMF0::Utf8Free(&pKey);
	AMF0::DataFree(&pValue);

	return ret;
}

void CCommandConnect::SetApp(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	memcpy(cObj->app,pValue->buf,pValue->len);
}

void CCommandConnect::SetFlashver(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	memcpy(cObj->flashver, pValue->buf, pValue->len);
}

void CCommandConnect::SetSwfUrl(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	memcpy(cObj->swfUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetTcUrl(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	memcpy(cObj->tcUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetFpad(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	if (*(pValue->buf) == 0)
		cObj->fpad = false;
	else
		cObj->fpad = true;
}

void CCommandConnect::SetAudioCodecs(void* pObj, AMF0::Data* pValue)
{
	//8个字节的大端模式
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	double src = 0;

	memcpy(&src,pValue->buf,pValue->len);
	cObj->audioCodecs = BigToHostDouble(src);
}

void CCommandConnect::SetVideoCodecs(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	cObj->videoCodecs = BigToHostDouble(src);
}

void CCommandConnect::SetVideoFunction(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	cObj->videoFunction = BigToHostDouble(src);
}

void CCommandConnect::SetPageUrl(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	memcpy(cObj->pageUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetObjectEncoding(void* pObj, AMF0::Data* pValue)
{
	CCommandConnect::Object *cObj = (CCommandConnect::Object*)pObj;
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	cObj->objectEncoding = BigToHostDouble(src);
}

CCommandConnect::Object* CCommandConnect::GetObject()
{
	return m_Obj;
}

uint8_t* CCommandConnect::TranslatePayload(CCommandConnect::Object* pObj, uint32_t *outLenght)
{
	return NULL;
}