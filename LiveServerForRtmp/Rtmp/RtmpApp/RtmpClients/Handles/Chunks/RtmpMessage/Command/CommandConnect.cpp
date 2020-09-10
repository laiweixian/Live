#include "stdafx.h"
#include "CommandConnect.h"


CCommandConnect::CCommandConnect():m_Obj(NULL)
{
}


CCommandConnect::~CCommandConnect()
{
}

ConnectObject* CCommandConnect::HandleConnect(AMF0::CParse *parse)
{
	
	AMF0::Data* pCommandObject = NULL;
	ConnectObject *pObj = NULL;

	pCommandObject = parse->m_Datas.at(2);
	
	pObj = new ConnectObject;
	memset(pObj, 0, sizeof(ConnectObject));

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
	return pObj;
}

int CCommandConnect::SetObject(AMF0::Data* pData, const char* key, ConnectObject *pObj,SetValue sVal)
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


void CCommandConnect::SetApp(ConnectObject* pObj, AMF0::Data* pValue)
{
	memcpy(pObj->app,pValue->buf,pValue->len);
}

void CCommandConnect::SetFlashver(ConnectObject* pObj, AMF0::Data* pValue)
{
	memcpy(pObj->flashver, pValue->buf, pValue->len);
}

void CCommandConnect::SetSwfUrl(ConnectObject* pObj, AMF0::Data* pValue)
{
	memcpy(pObj->swfUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetTcUrl(ConnectObject* pObj, AMF0::Data* pValue)
{
	memcpy(pObj->tcUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetFpad(ConnectObject* pObj, AMF0::Data* pValue)
{
	if (*(pValue->buf) == 0)
		pObj->fpad = false;
	else
		pObj->fpad = true;
}

void CCommandConnect::SetAudioCodecs(ConnectObject* pObj, AMF0::Data* pValue)
{
	//8个字节的大端模式
	double src = 0;

	memcpy(&src,pValue->buf,pValue->len);
	pObj->audioCodecs = BigToHostDouble(src);
}

void CCommandConnect::SetVideoCodecs(ConnectObject* pObj, AMF0::Data* pValue)
{
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	pObj->videoCodecs = BigToHostDouble(src);
}

void CCommandConnect::SetVideoFunction(ConnectObject* pObj, AMF0::Data* pValue)
{
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	pObj->videoFunction = BigToHostDouble(src);
}

void CCommandConnect::SetPageUrl(ConnectObject* pObj, AMF0::Data* pValue)
{
	memcpy(pObj->pageUrl, pValue->buf, pValue->len);
}

void CCommandConnect::SetObjectEncoding(ConnectObject* pObj, AMF0::Data* pValue)
{
	double src = 0;

	memcpy(&src, pValue->buf, pValue->len);
	pObj->objectEncoding = BigToHostDouble(src);
}