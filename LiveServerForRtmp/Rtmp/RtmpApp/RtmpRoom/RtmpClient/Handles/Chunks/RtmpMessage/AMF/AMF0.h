#pragma once

#include "stdafx.h"

namespace AMF0
{
	#define AMF0_OK				0
	#define AMF0_FAILURE		1
	#define ERROR_INPUT			-1		//INVALID_INPUT_ARGS
	#define ERROR_LOSS_DATA		-2		//OUT_OF_DATA
	#define ERROR_INVALID_TYHE	-3		//NO_THIS_TYPE
	#define ERROR_INVALID_UTF8	-4		//INVALID_UTF8_CHAR

	struct NullData {};
	

	typedef uint8_t		U8;
	typedef uint16_t	U16;
	typedef int16_t		S16;
	typedef uint32_t	U32;
	typedef double		DOUBLE;
	
	struct UTF8 {uint8_t* ptr;int len;};

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
		Number dNum;
		Boolean dBoo;
		String dStr;
		Object dObj;
		Movieclip dMov;
		Null dNul;
		Undefined dUnd;
		Reference dRef;
		ECMA_Array dECMA;
		ObjectEnd dObjEnd;
		StrictArray dStrArr;
		Date dDat;
		LongString dLonStr;
		Unsupported dUns;
		RecordSet dRec;
		XML_Document dXML;
		TypedObject dType;
	};
	struct Data
	{
		DataType dType;
		Variable dValue;
	};
	
	struct Number{DOUBLE value;};
	struct Boolean{U8 value;};
	struct String{UTF8 value;};
	struct ObjectProperty{UTF8 name; Data value;};
	struct Object {ObjectProperty* pObjPros; int objProCount;};
	typedef NullData Movieclip;
	typedef NullData Null;
	typedef NullData Undefined;
	struct Reference{U16 value;};
	struct ECMA_Array{U32 count;ObjectProperty* pObjPros;};
	typedef NullData ObjectEnd;
	struct StrictArray {U32 count;Data* pValues;};
	struct Date{DOUBLE value;};
	typedef String LongString;
	typedef NullData Unsupported;
	typedef NullData RecordSet;
	typedef	LongString XML_Document;
	struct TypedObject {UTF8 className; ObjectProperty* pObjPros; int count;};

	void ObjectProperty_free(ObjectProperty &objPro);
	void Object_free(Object& obj);
	void ECMA_Array_free(ECMA_Array& ecma);
	void StrictArray_free(StrictArray& stri);
	void TypedObject_free(TypedObject& typeObj);

	

	void UTF8_free(UTF8 &utf8);
	void AMF0Object_free(AMF0Object &amfObject);
	void AMF0EcmaArray_free(AMF0EcmaArray &ecma);
	void AMF0StrictArray_free(AMF0StrictArray &strict);
	void AMF0TypeObject_free(AMF0TypeObject& typeObject);
	void AMF0Data_free(AMF0Data &amfData);

	AMF0Data* amf0_malloc(AMF0Type aType);
	void amf0_free(AMF0Data** pamf);
}



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