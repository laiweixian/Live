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

#define DELCARE_FREE(TYPE)	\
	void TYPE##_free(TYPE& val);	\
	void TYPE##_copy(TYPE& dst, TYPE& src);

namespace AMF0
{
	struct NullData;
	struct Utf8String;
	struct Number;
	struct Boolean;
	struct String;
	struct Object;
	struct Movieclip;
	struct AMF0Null;
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
	struct Data;

	enum DataType;
	union Variable;
	class CParse;

	static const uint8_t  MARKER_NUMBER	= 1;
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

	union DataUnion
	{
		NullData *pNullData;		// not use/support
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

	struct NullData {};
	struct Utf8String { uint8_t* ptr;uint64_t len; };
	struct Number { DOUBLE num; };
	struct Boolean { U8 bol; };
	struct String { Utf8String utf8; };
	struct ObjectProperty { Utf8String name; Data value; };
	struct Object { U32 count; ObjectProperty* pObjPros; };
	typedef NullData Movieclip;
	typedef NullData AMF0Null;
	typedef NullData Undefined;
	struct Reference { U16 ref; };
	struct ECMA_Array { U32 count;ObjectProperty* pObjPros; };
	typedef NullData ObjectEnd;
	struct StrictArray { U32 count;Data* pValues; };
	struct Date { DOUBLE date; };
	struct LongString { Utf8String utf8Long; };
	typedef NullData Unsupported;
	typedef NullData RecordSet;
	typedef	LongString XML_Document;
	struct TypedObject { Utf8String className; U32 count; ObjectProperty* pObjPros; };
	struct Data{ uint8_t dType; DataUnion dValue;};

	DELCARE_FREE(NullData)
	DELCARE_FREE(Utf8String)
	DELCARE_FREE(Number)
	DELCARE_FREE(Boolean)
	DELCARE_FREE(String)
	DELCARE_FREE(ObjectProperty)
	DELCARE_FREE(Object)
	DELCARE_FREE(Movieclip)
	DELCARE_FREE(AMF0Null)
	DELCARE_FREE(Undefined)
	DELCARE_FREE(Reference)
	DELCARE_FREE(ECMA_Array)
	DELCARE_FREE(ObjectEnd)
	DELCARE_FREE(StrictArray)
	DELCARE_FREE(Date)
	DELCARE_FREE(LongString)
	DELCARE_FREE(Unsupported)
	DELCARE_FREE(RecordSet)
	DELCARE_FREE(XML_Document)
	DELCARE_FREE(TypedObject)
	DELCARE_FREE(Data)

	void UTF8ToString(string &str, Utf8String& utf8);
	bool UTF8IsEqual(const char* str, Utf8String& utf8);

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

		static int ParseUtf8(uint8_t *src, const int srcLen, Utf8String &utf8, int* outLen);
		static int ParseUtf8Long(uint8_t *src, const int srcLen, Utf8String &utf8Long, int* outLen);
		static int ParseObjectProperty(uint8_t *src, const int srcLen, ObjectProperty& objPro, int* outLen);
	public:
		std::vector<Data*> m_Datas;
	};


};







