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
	static const U8  MARKER_NONE = 0xFF;
	static const U8  MARKER_NUMBER = 0x00;
	static const U8  MARKER_BOOLEAN = 0x01;
	static const U8  MARKER_STRING = 0x02;
	static const U8  MARKER_OBJECT = 0x03;
	static const U8  MARKER_MOVIECLIP = 0x04;/*reserved , not supported*/
	static const U8  MARKER_NULL = 0x05;
	static const U8  MARKER_UNDEFINED = 0x06;
	static const U8  MARKER_REFERENCE = 0x07;
	static const U8  MARKER_ECMA_ARRAY = 0x08;
	static const U8  MARKER_OBJECT_END = 0x09;
	static const U8  MARKER_STRICT_ARRAY = 0x0a;
	static const U8  MARKER_DATE = 0x0b;
	static const U8  MARKER_LONG_STRING = 0x0c;
	static const U8  MARKER_UNSUPPORTED = 0x0d;
	static const U8  MARKER_RECORDSET = 0x0e;/*reserved , not support*/
	static const U8  MARKER_XML_DOCUMENT = 0x0f;
	static const U8  MARKER_TYPE_OBJECT = 0x10;

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
	bool CompareUtf8(UTF8& u1,UTF8& u2);
	void CopyData(Data& dst,Data& src);
	void Utf8Free(UTF8** ppUtf8);
	void DataFree(Data** ppData);
	UTF8* Convert(const char* c);
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

	static int MatchField(Data& src,UTF8 key,Data& value);

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