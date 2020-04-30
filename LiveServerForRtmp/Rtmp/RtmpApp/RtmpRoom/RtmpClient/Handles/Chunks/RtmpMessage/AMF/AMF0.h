#pragma once

#include "stdafx.h"

namespace AMF0
{
	struct NullData {};
	typedef uint8_t		U8;
	typedef uint16_t	U16;
	typedef int16_t		S16;
	typedef uint32_t	U32;
	typedef double		DOUBLE;
	
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
	
	enum DataType
	{
		NONE = 0xFF,
		NUMBER = 0x00, BOOLEAN, STRING, OBJECT,
		MOVIECLIP /*reserved , not supported*/, NULL_MARKER, UNDEFINED, REFERENCE,
		ECMA_ARRAY, OBJECT_END, STRICT_ARRAY, DATE,
		LONG_STRING, UNSUPPORTED, RECORDSET/*reserved , not support*/, XML_DOCUMENT,
		TYPE_OBJECT
	};
	union Variable
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
	struct Data
	{
		DataType dType;
		Variable dValue;
	};

	struct Utf8String { uint8_t* ptr;uint64_t len; };
	struct Number { DOUBLE num; };
	struct Boolean { U8 bol; };
	struct String { Utf8String utf8; };
	struct ObjectProperty { Utf8String name; Data value; };
	struct Object { U32 count; ObjectProperty* pObjPros;  };
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
	struct TypedObject { Utf8String className; U32 count; ObjectProperty* pObjPros;  };


#define DELCARE_FREE(TYPE)	\
	void TYPE##_free(TYPE& val);\
	void TYPE##_copy(TYPE& dst,TYPE& src);

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

	#define AMF0_OK				0
	#define AMF0_FAILURE		1
	#define END_OF_OBJECT	    3
	#define NO_END_OF_OBJECT	4
	#define ERROR_INPUT			-1		//INVALID_INPUT_ARGS
	#define ERROR_LOSS_DATA		-2		//OUT_OF_DATA
	#define ERROR_INVALID_TYHE	-3		//NO_THIS_TYPE
	#define ERROR_INVALID_UTF8	-4		//INVALID_UTF8_CHAR
	class CParse
	{
	private:
		CParse();
		~CParse();
	public:
		static CParse* Create(uint8_t *src, const int srcLen);
		void Destroy();
	private:
		static int ParseData(uint8_t *src, const int srcLen,Data& data,int *outOffset);
		static int ParseNumber(uint8_t *src, const int srcLen, Number& number, int* outOffset);
		static int ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outOffset);
		static int ParseString(uint8_t *src, const int srcLen, String& str, int* outOffset);
		static int ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outOffset);
		static int ParseMovieClip(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseNull(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseUndefined(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseReference(uint8_t *src, const int srcLen, Reference &refer, int* outOffset);
		static int ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outOffset);
		static int ParseObjectEnd(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseStrictArray(uint8_t *src, const int srcLen, StrictArray& strictArray, int* outOffset);
		static int ParseDate(uint8_t *src, const int srcLen, Date& date, int* outOffset);
		static int ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outOffset);
		static int ParseUnsupported(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseRecordSet(uint8_t *src, const int srcLen, int* outOffset);
		static int ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &utf8, int* outOffset);
		static int ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outOffset);

		static int ParseUtf8(uint8_t *src, const int srcLen, Utf8String &utf8, int* outOffset);
		static int ParseUtf8Long(uint8_t *src, const int srcLen, Utf8String &utf8Long, int* outOffset);
		static int ParseObjectProperty(uint8_t *src, const int srcLen, ObjectProperty& objPro, int* outOffset);
	public:
		std::vector<Data*> m_Datas;
	};

}

void UTF8ToString(string &str, AMF0::Utf8String& utf8);
bool UTF8IsEqual(const char* str, AMF0::Utf8String& utf8);