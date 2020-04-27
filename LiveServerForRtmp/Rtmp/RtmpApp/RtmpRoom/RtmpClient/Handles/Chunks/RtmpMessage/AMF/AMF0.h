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
	
	
	struct Utf8String{ uint8_t* ptr;uint64_t len; };
	struct Number{DOUBLE num;};
	struct Boolean{U8 bol;};
	struct String{ Utf8String utf8;};
	struct ObjectProperty{ Utf8String name; Data value;};
	struct Object {ObjectProperty* pObjPros; int objProCount;};
	typedef NullData Movieclip;
	typedef NullData AMF0Null;
	typedef NullData Undefined;
	struct Reference{U16 ref;};
	struct ECMA_Array{U32 count;ObjectProperty* pObjPros;};
	typedef NullData ObjectEnd;
	struct StrictArray {U32 count;Data* pValues;};
	struct Date{DOUBLE date;};
	struct LongString{ Utf8String utf8Long;};
	typedef NullData Unsupported;
	typedef NullData RecordSet;
	typedef	LongString XML_Document;
	struct TypedObject { Utf8String className; ObjectProperty* pObjPros; int count;};

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



#define DECLARE_TYPE_FREE(TYPE)		\
	void TYPE##_init(TYPE &val);	\
	void TYPE##_free(TYPE &val);	\
	void TYPE##_copy(TYPE &dst,TYPE &src);

	DECLARE_TYPE_FREE(Utf8String)
	DECLARE_TYPE_FREE(NullData)
	DECLARE_TYPE_FREE(Number)
	DECLARE_TYPE_FREE(Boolean)
	DECLARE_TYPE_FREE(String)
	DECLARE_TYPE_FREE(Object)
	DECLARE_TYPE_FREE(Movieclip)
	DECLARE_TYPE_FREE(AMF0Null)
	DECLARE_TYPE_FREE(Undefined)
	DECLARE_TYPE_FREE(Reference)
	DECLARE_TYPE_FREE(ECMA_Array)
	DECLARE_TYPE_FREE(ObjectEnd)
	DECLARE_TYPE_FREE(StrictArray)
	DECLARE_TYPE_FREE(Date)
	DECLARE_TYPE_FREE(LongString)
	DECLARE_TYPE_FREE(Unsupported)
	DECLARE_TYPE_FREE(RecordSet)
	DECLARE_TYPE_FREE(XML_Document)
	DECLARE_TYPE_FREE(TypedObject)

	void ObjectProperty_init(ObjectProperty &val, DataType dtype);
	void ObjectProperty_free(ObjectProperty &val);
	
	void Data_init(Data& data,DataType dtype);
	void Data_free(Data& data);
	void Data_Copy(Data& dst,Data& src);

	#define AMF0_OK				0
	#define AMF0_FAILURE		1
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
		static Data* ParseData(uint8_t *src, const int srcLen,int *outOffset);
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
	public:
		std::vector<Data*> m_Datas;
	};
}



/*
class CAMF0
{
private:
	CAMF0();
	~CAMF0();

public:
	static CAMF0* CreateAMF0( uint8_t *pData,const int dataLen);
	void Destroy();
private:
	int Init(uint8_t *pData, const int dataLen);
	static AMF0Data* Parse(uint8_t *pData, const int dataLen,int* outOffset);
	static int ParseNumber(uint8_t *pData, const int dataLen, DOUBLE& number, int* outOffset);
	static int ParseBoolean(uint8_t *pData, const int dataLen, U8& boolData, int* outOffset);
	static int ParseString(uint8_t *pData, const int dataLen, UTF8& utf8, int* outOffset);
	static int ParseObject(uint8_t *pData, const int dataLen, AMF0Object& amfObj, int* outOffset);
	static int ParseMovieClip(uint8_t *pData, const int dataLen, int* outOffset);
	static int ParseNull(uint8_t *pData, const int dataLen, int* outOffset);
	static int ParseUndefined(uint8_t *pData, const int dataLen,  int* outOffset);
	static int ParseReference(uint8_t *pData, const int dataLen, U16 &refer, int* outOffset);
	static int ParseEcmaArray(uint8_t *pData, const int dataLen, AMF0EcmaArray &ecma, int* outOffset);
	static int ParseObjectEnd(uint8_t *pData, const int dataLen,  int* outOffset);
	static int ParseStrictArray(uint8_t *pData, const int dataLen, AMF0StrictArray& strictArray, int* outOffset);
	static int ParseDate(uint8_t *pData, const int dataLen, DOUBLE& date, int* outOffset);
	static int ParseLongString(uint8_t *pData, const int dataLen, UTF8 &utf8, int* outOffset);
	static int ParseUnsupported(uint8_t *pData, const int dataLen,  int* outOffset);
	static int ParseRecordSet(uint8_t *pData, const int dataLen, int* outOffset);
	static int ParseXmlDocument(uint8_t *pData, const int dataLen, UTF8 &utf8, int* outOffset);
	static int ParseTypeObject(uint8_t *pData, const int dataLen, AMF0TypeObject &typeObject, int* outOffset);
	
	static int ParseUTF8(uint8_t *pData,const int dataLen,UTF8& utf8,int *outOffset);
	static int ParseUTF8Long(uint8_t *pData, const int dataLen, UTF8& utf8, int *outOffset);
public:
	vector<AMF0Data*> m_Amfs;
};


static void UTF8ToString(string &str, UTF8 utf8)
{
	char *c = NULL;

	c = new char[utf8.buffLength+1];
	memset(c,0, utf8.buffLength + 1);
	memcpy(c,utf8.buff, utf8.buffLength);

	str = c;
	
	delete[] c;
}

static bool UTF8IsEqual(const char* str, UTF8 utf8)
{
	char *c = NULL;
	int ret = 0;

	c = new char[utf8.buffLength + 1];
	memset(c, 0, utf8.buffLength + 1);
	memcpy(c, utf8.buff, utf8.buffLength);

	ret = strcmp(str,c);
	delete[] c;

	return (ret == 0);
}

*/