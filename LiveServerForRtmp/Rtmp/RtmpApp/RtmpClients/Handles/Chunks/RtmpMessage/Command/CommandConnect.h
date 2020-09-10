#pragma once

#include "../../Receive/BaseMessage.h"
#include "../AMF/AMF.h"

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

struct ConnectObject
{
	char* app;
	char* flashver;
	char* swfUrl;
	char* tcUrl;
	char* fpad;
	char* audioCodecs;
	char* videoCodecs;
	char* videoFunction;
	char* pageUrl;
	char* objectEncoding;
};

typedef void(*SetValue)(ConnectObject* pObj,AMF0::Data* pValue);

class CCommandConnect
{
public:
	CCommandConnect();
	virtual ~CCommandConnect();
protected:
	ConnectObject* HandleConnect(AMF0::CParse *parse);
private:
	int SetObject(AMF0::Data* pData, const char* key, ConnectObject *pObj, SetValue sVal);
public:
	static void SetApp(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetFlashver(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetSwfUrl(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetTcUrl(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetFpad(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetAudioCodecs(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetVideoCodecs(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetVideoFunction(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetPageUrl(ConnectObject* pObj, AMF0::Data* pValue);
	static void SetObjectEncoding(ConnectObject* pObj, AMF0::Data* pValue);

};

