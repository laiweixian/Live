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

#define DELCARE_FUNC(TYPE)	\
	void TYPE##_free(TYPE& val);	\
	void TYPE##_copy(TYPE& dst, TYPE& src);

namespace AMF0
{
	struct Number { DOUBLE num; };
	struct Boolean { U8 bol; };
	typedef struct Utf8 { uint8_t* ptr;uint64_t len; } \
		String, \
		LongString, \
		XML_Document;
	typedef struct NullData { void* A; }\
		Movieclip, \
		AMF0Null, \
		Undefined, \
		ObjectEnd, \
		Unsupported, \
		RecordSet;

	struct ObjectProperty { Utf8 name; Data value; };
	struct Object { U32 count; ObjectProperty* pObjPros; };
	struct Reference { U16 ref; };
	struct ECMA_Array { U32 count;ObjectProperty* pObjPros; };
	struct StrictArray { U32 count;Data* pValues; };
	struct Date { DOUBLE date; };
	struct TypedObject { Utf8 className; U32 count; ObjectProperty* pObjPros; };

	union Variable
	{
		Number *pNum;
		Boolean *pBool;
		String *pStr;
		Object *pObj;
		Movieclip *pMov;			//not use/support
		AMF0Null *pNull;			//not use/support
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
	struct Data { uint8_t dType; Variable dValue; };

	

	DELCARE_FUNC(Number)
	DELCARE_FUNC(Boolean)
	DELCARE_FUNC(Utf8)
	DELCARE_FUNC(NullData)
	DELCARE_FUNC(ObjectProperty)
	DELCARE_FUNC(Object)
	DELCARE_FUNC(Reference)
	DELCARE_FUNC(ECMA_Array)
	DELCARE_FUNC(StrictArray)
	DELCARE_FUNC(Date)
	DELCARE_FUNC(TypedObject)
	DELCARE_FUNC(Data)

	void UTF8ToString(string &str, Utf8& utf8);
	bool UTF8IsEqual(const char* str, Utf8& utf8);

	class CParse
	{
	private:
		CParse();
		~CParse();
	public:
		static CParse* Create(uint8_t *src, const int srcLen);
		void Destroy();
	private:
		static int ParseData(uint8_t *src, const int srcLen, Data& data, int *outLen);
		static int ParseNumber(uint8_t *src, const int srcLen, Number& number, int* outLen);
		static int ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outLen);
		static int ParseString(uint8_t *src, const int srcLen, String& str, int* outLen);
		static int ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outLen);
		static int ParseMovieClip(uint8_t *src, const int srcLen, int* outLen);
		static int ParseNull(uint8_t *src, const int srcLen, int* outLen);
		static int ParseUndefined(uint8_t *src, const int srcLen, int* outLen);
		static int ParseReference(uint8_t *src, const int srcLen, Reference &refer, int* outLen);
		static int ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outLen);
		static int ParseObjectEnd(uint8_t *src, const int srcLen, int* outLen);
		static int ParseStrictArray(uint8_t *src, const int srcLen, StrictArray& strictArray, int* outLen);
		static int ParseDate(uint8_t *src, const int srcLen, Date& date, int* outLen);
		static int ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outLen);
		static int ParseUnsupported(uint8_t *src, const int srcLen, int* outLen);
		static int ParseRecordSet(uint8_t *src, const int srcLen, int* outLen);
		static int ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &utf8, int* outLen);
		static int ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outLen);
		static int ParseObjectProperty(uint8_t *src, const int srcLen, ObjectProperty& objPro, int* outLen);
	public:
		std::vector<Data*> m_Datas;
	};


};







