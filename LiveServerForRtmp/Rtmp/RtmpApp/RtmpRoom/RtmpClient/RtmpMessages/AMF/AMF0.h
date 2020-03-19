#pragma once

#include "stdafx.h"


typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;


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
		DOUBLE data_num;			//NUMBER
		U8	   data_bool;			//BOOLEAN
		UTF8   data_utf8;			//UTF-8 CHAR
		AMF0Object data_object;		//OBJECT
		U16		data_reference;		//REFERENCE 
		AMF0EcmaArray data_ecma_array;	//ECMA ARRAY
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

