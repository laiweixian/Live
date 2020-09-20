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



typedef void(*SetValue)(void* pObj,AMF0::Data* pValue);

class CCommandConnect
{
public:
	struct Object {
		char app[1024];
		char flashver[1024];
		char swfUrl[1024];
		char tcUrl[1024];
		bool fpad;
		double audioCodecs;
		double videoCodecs;
		double videoFunction;
		char pageUrl[1024];
		double objectEncoding;
	};

	struct Response{};

public:
	CCommandConnect();
	 ~CCommandConnect();

	 static Object* Decode(AMF0::CParse *parse);
	  
private:
	static void SetObject(AMF0::Data* pData, const char* key, Object *pObj, SetValue sVal);
	static void SetApp(void* pObj, AMF0::Data* pValue);
	static void SetFlashver(void* pObj, AMF0::Data* pValue);
	static void SetSwfUrl(void* pObj, AMF0::Data* pValue);
	static void SetTcUrl(void* pObj, AMF0::Data* pValue);
	static void SetFpad(void* pObj, AMF0::Data* pValue);
	static void SetAudioCodecs(void* pObj, AMF0::Data* pValue);
	static void SetVideoCodecs(void* pObj, AMF0::Data* pValue);
	static void SetVideoFunction(void* pObj, AMF0::Data* pValue);
	static void SetPageUrl(void* pObj, AMF0::Data* pValue);
	static void SetObjectEncoding(void* pObj, AMF0::Data* pValue);

};

