#pragma once

#include "stdafx.h"

#define INVALID_INPUT_ARGS	-1
#define OUT_OF_DATA			-2
#define NO_THIS_TYPE		-3
#define INVALID_UTF8_CHAR	-4

typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;

struct UTF8;
struct ObjectMember;
struct AMF0Object;
struct AMF0EcmaArray;
struct AMF0StrictArray;
struct AMF0TypeObject;
struct AMF0Data;


void UTF8_free(UTF8 &utf8);
void AMF0Object_free(AMF0Object &amfObject);
void AMF0EcmaArray_free(AMF0EcmaArray &ecma);
void AMF0StrictArray_free(AMF0StrictArray &strict);
void AMF0TypeObject_free(AMF0TypeObject& typeObject);
void AMF0Data_free(AMF0Data &amfData);

AMF0Data* amf0_malloc(AMF0Type aType);
void amf0_free(AMF0Data** pamf);

struct UTF8
{
	uint8_t *buff;
	uint64_t buffLength;
};

struct ObjectMember
{
	UTF8 name;
	AMF0Data value;
};

struct AMF0Object
{
	ObjectMember *pMems;
	uint32_t MemCount;
};

struct AMF0EcmaArray
{
	AMF0Object *pObjects;
	int			objCount ;
};

struct AMF0StrictArray
{
	AMF0Data *pAMFData;
	int		  amfDataCount;
};

struct AMF0TypeObject
{
	UTF8 className;
	AMF0Object *pObjects;
	int			objCount;
};

enum AMF0Type
{
	NONE = 0xFF,
	NUMBER = 0x00, BOOLEAN, STRING, OBJECT,
	MOVIECLIP /*reserved , not supported*/, NULL_MARKER, UNDEFINED, REFERENCE,
	ECMA_ARRAY, OBJECT_END, STRICT_ARRAY, DATE,
	LONG_STRING, UNSUPPORTED, RECORDSET/*reserved , not support*/, XML_DOCUMENT,
	TYPE_OBJECT
};

struct AMF0Data
{
	AMF0Type dType;
	
	DOUBLE *pNumber;					//NUMBER
	U8	   *pBoolean;					//BOOLEAN
	UTF8   *pString;					//UTF-8 CHAR
	AMF0Object *pObject;				//OBJECT
	U16		*pReference;				//REFERENCE 
	AMF0EcmaArray *pEcmaArray;		//ECMA ARRAY
	AMF0StrictArray *pStrictArray;	//STRICT ARRAY
	DOUBLE	*pDate;					//DATE
	UTF8	*pStringLong;				//LONG UTF-8 CHAR
	UTF8	*pXmlDocument;			//XML
	AMF0TypeObject *pTypeObject;	//TYPE OBJECT 
	void* *pReserved;		//reserved
	
};

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