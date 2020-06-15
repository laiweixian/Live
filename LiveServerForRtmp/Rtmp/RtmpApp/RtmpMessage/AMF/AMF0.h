#pragma once

#include "stdafx.h"

#define AMF0_OK				0
#define AMF0_FAILURE		1


typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;


namespace AMF0
{
	static const uint8_t  MARKER_NUMBER = 1;
	static const uint8_t  MARKER_BOOLEAN = 2;
	static const uint8_t  MARKER_STRING = 3;
	static const uint8_t  MARKER_OBJECT = 4;
	static const uint8_t  MARKER_MOVIECLIP = 5;/*reserved , not supported*/
	static const uint8_t  MARKER_NULL = 6;
	static const uint8_t  MARKER_UNDEFINED = 7;
	static const uint8_t  MARKER_REFERENCE = 8;
	static const uint8_t  MARKER_ECMA_ARRAY = 9;
	static const uint8_t  MARKER_OBJECT_END = 10;
	static const uint8_t  MARKER_STRICT_ARRAY = 11;
	static const uint8_t  MARKER_DATE = 12;
	static const uint8_t  MARKER_LONG_STRING = 13;
	static const uint8_t  MARKER_UNSUPPORTED = 14;
	static const uint8_t  MARKER_RECORDSET = 15;/*reserved , not support*/
	static const uint8_t  MARKER_XML_DOCUMENT = 16;
	static const uint8_t  MARKER_TYPE_OBJECT = 17;

	typedef struct Data{
		uint8_t marker;
		uint8_t *buf;
		uint64_t len;
	}Number, Boolean, String, Object,\
	Reference, ECMA_Array, StrictArray,\
	Date, LongString,XML_Document, TypedObject;

	typedef struct UTF8
	{
		uint8_t *buf;
		uint64_t len ;
	};

	void AllocDataBuff(Data& data,uint8_t* src,uint64_t len);
	bool IsNumber(Data& data);
	bool IsBoolean(Data& data);
	bool IsString(Data& data);
	bool IsObject(Data& data);
	bool IsReference(Data& data);
	bool IsECMA_Array(Data& data);
	bool IsStrictArray(Data& data);
	bool IsDate(Data& data);
	bool IsXMLDocument(Data& data);
	bool IsTypeObject(Data& data);

	int ParseUTF8(uint8_t* src,uint32_t len, UTF8& utf8,int *outLen);
	int ParseUTF8Long(uint8_t* src, uint32_t len, UTF8& utf8, int *outLen);

	int ParseObject(Data& data,int *outLen);

	class CParse;
};



class AMF0::CParse
{
private:
	CParse();
	~CParse();
public:
	static CParse* Create(uint8_t *src, const int srcLen);
	void Destroy();
private:
	static int ParseData(uint8_t *src, const int srcLen, AMF0::Data& data, int *outLen);
	static int ParseNumber(uint8_t *src, const int srcLen, AMF0::Number& number, int* outLen);
	static int ParseBoolean(uint8_t *src, const int srcLen, AMF0::Boolean& boolData, int* outLen);
	static int ParseString(uint8_t *src, const int srcLen, AMF0::String& str, int* outLen);
	static int ParseObject(uint8_t *src, const int srcLen, AMF0::Object& obj, int* outLen);
	static int ParseMovieClip(uint8_t *src, const int srcLen, int* outLen);
	static int ParseNull(uint8_t *src, const int srcLen, int* outLen);
	static int ParseUndefined(uint8_t *src, const int srcLen, int* outLen);
	static int ParseReference(uint8_t *src, const int srcLen, AMF0::Reference &refer, int* outLen);
	static int ParseEcmaArray(uint8_t *src, const int srcLen, AMF0::ECMA_Array &ecma, int* outLen);
	static int ParseObjectEnd(uint8_t *src, const int srcLen, int* outLen);
	static int ParseStrictArray(uint8_t *src, const int srcLen, AMF0::StrictArray& strictArray, int* outLen);
	static int ParseDate(uint8_t *src, const int srcLen, AMF0::Date& date, int* outLen);
	static int ParseLongString(uint8_t *src, const int srcLen, AMF0::LongString &longStr, int* outLen);
	static int ParseUnsupported(uint8_t *src, const int srcLen, int* outLen);
	static int ParseRecordSet(uint8_t *src, const int srcLen, int* outLen);
	static int ParseXmlDocument(uint8_t *src, const int srcLen, AMF0::XML_Document &xml, int* outLen);
	static int ParseTypeObject(uint8_t *src, const int srcLen, AMF0::TypedObject &typeObject, int* outLen);
	
public:
	std::vector<AMF0::Data*> m_Datas;
};