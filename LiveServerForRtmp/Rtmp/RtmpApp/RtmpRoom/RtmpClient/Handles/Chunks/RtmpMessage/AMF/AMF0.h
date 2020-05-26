#pragma once

#include "stdafx.h"

#define AMF0_OK				0
#define AMF0_FAILURE		1
#define END_OF_OBJECT	    3
#define NO_END_OF_OBJECT	4
#define ERROR_INPUT			-1		//INVALID_INPUT_ARGS
#define ERROR_LOSS_DATA		-2		//OUT_OF_DATA
#define ERROR_INVALID_TYHE	-3		//NO_THIS_TYPE
#define ERROR_INVALID_UTF8	-4		//INVALID_UTF8_CHAR

typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;



struct Utf8 { uint8_t* ptr;uint64_t len; };
struct NullData { void *p; };

void Utf8_copy(Utf8& dst, Utf8& src);
void Utf8_free(Utf8& utf8);

void UTF8ToString(string &str, Utf8& utf8);
bool UTF8IsEqual(const char* str, Utf8& utf8);

#define DELCARE_FUNC(TYPE)	\
	void TYPE##_free(TYPE& val);	\
	void TYPE##_copy(TYPE& dst, TYPE& src);

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

	struct Number;
	struct Boolean;
	struct String;
	struct Object;
	struct Movieclip;
	struct Null;
	struct Undefined;
	struct Reference;
	struct ECMA_Array;
	struct ObjectEnd;
	struct StrictArray;
	struct Date;
	struct LongString;
	struct Unsupported;
	struct RecordSet;
	struct XML_Document;
	struct TypedObject;
	
	union Variable
	{
		Number *pNum;
		Boolean *pBool;
		String *pStr;
		Object *pObj;
		Movieclip *pMov;			//not use/support
		Null *pNull;			//not use/support
		Undefined *pUnd;			//not use/support
		Reference *pRef;
		ECMA_Array *pECMA;
		ObjectEnd *pObjEnd;			//not use/support
		StrictArray *pStrArr;
		Date *pDate;
		LongString *pLonStr;
		Unsupported *pUns;			//not use/support
		RecordSet *pRec;			//not use/support
		XML_Document *pXML;
		TypedObject *pTypeObj;
	};

	struct Member;
	struct Data;

	DELCARE_FUNC(Number)
	DELCARE_FUNC(Boolean)
	DELCARE_FUNC(String)
	DELCARE_FUNC(Object)
	DELCARE_FUNC(Movieclip)
	DELCARE_FUNC(Null)
	DELCARE_FUNC(Undefined)
	DELCARE_FUNC(Reference)
	DELCARE_FUNC(ECMA_Array)
	DELCARE_FUNC(ObjectEnd)
	DELCARE_FUNC(StrictArray)
	DELCARE_FUNC(Date)
	DELCARE_FUNC(LongString)
	DELCARE_FUNC(Unsupported)
	DELCARE_FUNC(RecordSet)
	DELCARE_FUNC(XML_Document)
	DELCARE_FUNC(TypedObject)
	DELCARE_FUNC(Member)
	DELCARE_FUNC(Data)


	class CParse;
};

struct AMF0::Number{DOUBLE num;};
struct AMF0::Boolean{U8 bol;};
struct AMF0::String{Utf8 utf8;};
struct AMF0::LongString{Utf8 utf8;};
struct AMF0::XML_Document{Utf8 utf8;};
struct AMF0::Movieclip{ NullData  nData;};
struct AMF0::Null { NullData  nData; };
struct AMF0::Undefined { NullData  nData; };
struct AMF0::ObjectEnd { NullData  nData; };
struct AMF0::Unsupported { NullData  nData; };
struct AMF0::RecordSet { NullData  nData; };
struct AMF0::Object{ U32 count; AMF0::Member* pMems; };
struct AMF0::Reference{ U16 ref;};
struct AMF0::ECMA_Array{U32 count;AMF0::Member *pMems;};
struct AMF0::StrictArray{U32 count; AMF0::Data *pDatas;};
struct AMF0::Date{ DOUBLE date; };
struct AMF0::TypedObject { Utf8 className; U32 count; AMF0::Member* pMems; };
struct AMF0::Data { uint8_t dType; Variable dValue; };
struct AMF0::Member{Utf8 name;AMF0::Data value;};

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
	static int ParseLongString(uint8_t *src, const int srcLen, AMF0::LongString &utf8, int* outLen);
	static int ParseUnsupported(uint8_t *src, const int srcLen, int* outLen);
	static int ParseRecordSet(uint8_t *src, const int srcLen, int* outLen);
	static int ParseXmlDocument(uint8_t *src, const int srcLen, AMF0::XML_Document &utf8, int* outLen);
	static int ParseTypeObject(uint8_t *src, const int srcLen, AMF0::TypedObject &typeObject, int* outLen);
	static int ParseObjectProperty(uint8_t *src, const int srcLen, AMF0::Member& mem, int* outLen);
public:
	std::vector<AMF0::Data*> m_Datas;
};