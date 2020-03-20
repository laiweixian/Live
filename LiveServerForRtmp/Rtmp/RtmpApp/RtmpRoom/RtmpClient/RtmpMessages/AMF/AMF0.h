#pragma once

#include "stdafx.h"


typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;

struct UTF8;
struct AMF0Object;
struct AMF0EcmaArray;
struct AMF0StrictArray;
struct AMF0TypeObject;
struct AMF0Data;
struct AMF0Reserved;

void UTF8_free(UTF8 &utf8);
void AMF0Object_free(AMF0Object &amfObject);
void AMF0EcmaArray_free(AMF0EcmaArray &ecma);
void AMF0StrictArray_free(AMF0StrictArray &strict);
void AMF0TypeObject_free(AMF0TypeObject& typeObject);
void AMF0Data_free(AMF0Data &amfData);

AMF0Data* amf0_init();
void amf0_free(AMF0Data** pamf);

struct UTF8
{
	char *buff;
	int buffLength;
};

struct AMF0Object
{
	UTF8 *pUtf8s;
	int utf8Count;
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

struct AMF0Reserved{};


enum AMF0Type
{
	NUMBER = 0x00, BOOLEAN, STRING, OBJECT,
	MOVIECLIP /*reserved , not supported*/, NULL_MARKER, UNDEFINED, REFERENCE,
	ECMA_ARRAY, OBJECT_END, STRICT_ARRAY, DATE,
	LONG_STRING, UNSUPPORTED, RECORDSET/*reserved , not support*/, XML_DOCUMENT,
	TYPE_OBJECT
};




struct AMF0Data
{
	AMF0Type dType;
	union 
	{
		DOUBLE data_num;					//NUMBER
		U8	   data_bool;					//BOOLEAN
		UTF8   data_utf8;					//UTF-8 CHAR
		AMF0Object data_object;				//OBJECT
		U16		data_reference;				//REFERENCE 
		AMF0EcmaArray data_ecma_array;		//ECMA ARRAY
		AMF0StrictArray data_strict_array;	//STRICT ARRAY
		DOUBLE	data_date;					//DATE
		UTF8	data_utf8_long;				//LONG UTF-8 CHAR
		AMF0TypeObject data_type_object;	//TYPE OBJECT 
		AMF0Reserved *data_reserved;
	};
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
	int Splite( uint8_t *pData, const int dataLen);
	static int SpliteBasicType( uint8_t *pData, const int dataLen,AMF0Data *pAMF);
	static int SpliteCompositType( uint8_t *pData, const int dataLen,AMF0Data *pAMF);
public:
	vector<AMF0Data*> m_Datas;
};

