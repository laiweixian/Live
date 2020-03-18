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
	UTF8 *pUtf8;
	int utf8Count;
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
		DOUBLE data0;			//NUMBER
		U8	   data1;			//BOOLEAN
		UTF8   data2;			//UTF-8 CHAR
		AMF0Object data3;		//OBJECT
	};
};

class CAMF0
{
private:
	CAMF0();
	~CAMF0();

public:
	static CAMF0* CreateAMF0( uint8_t *pData,const int dataLen);
private:
	int Splite(uint8_t *pData, const int dataLen);
	int SpliteBasicType(uint8_t *pData, const int dataLen);
	int SpliteCompositType(uint8_t *pData, const int dataLen);
public:
	vector<AMF0Data*> m_Datas;
};

