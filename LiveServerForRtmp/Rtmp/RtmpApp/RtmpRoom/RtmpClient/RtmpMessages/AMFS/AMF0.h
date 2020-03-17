#pragma once

#include "stdafx.h"

typedef uint8_t		U8;
typedef uint16_t	U16;
typedef int16_t		S16;
typedef uint32_t	U32;
typedef double		DOUBLE;

#define NUMBER_MARKER		(0x00)
#define BOOLEAN_MARKET		(0x01)
#define STRING_MARKER		(0x02)
#define OBJECT_MARKER		(0x03)
#define MOVIECLIP_MARKER	(0x04)			//reserved , not supported
#define NULL_MARKER			(0x05)
#define UNDEFINED_MARKER	(0x06)
#define REFERENCE_MARKER	(0x07)
#define ECMA_ARRAY_MARKER	(0x08)
#define OBJECT_END_MARKER	(0x09)
#define STRICT_ARRAY_MARKER	(0x0a)
#define DATE_MARKER			(0x0b)
#define LONG_STRING_MARKER	(0x0c)
#define UNSUPPORTED_MARKER	(0x0d)
#define RECORDSET_MARKER	(0x0e)			//reserved , not support
#define XML_DOCUMENT_MARKER	(0x0f)
#define TYPE_OBJECT_MARKER	(0x10)

struct AMFData
{
	uint8_t dataType; 
	char *pData;
	int dataLen ;
};


static int  SpliteAMFData(uint8_t *pData,const int dataLen)
{
	
	
	



	return;
}

static int SplitBasicType(uint8_t *pData, const int dataLen, AMFData *pAmf)
{
	const uint8_t valueType = *pData;
	int offset = 0;
	char *pValue = NULL;
	int valueLen = 0;
	
	//用于string 的变量
	U16 utf8Length ;
	uint32_t length  = 0;
	int index = 0;
	char start = 0x00;
	bool c1 = false , c2 = false , c3 = false , c4 = false; 
	

	offset += 1;
	switch (valueType)
	{
	case NUMBER_MARKER:
		valueLen = sizeof(DOUBLE);
		if (dataLen < valueLen)
			return -1;
		pValue = new char[valueLen];
		break;
	case BOOLEAN_MARKET:
		valueLen = sizeof(U8);
		if (dataLen < valueLen)
			return -1;

		pValue = new char[valueLen];
		break;
	case STRING_MARKER:
		memcpy(&utf8Length,pData+offset,2);
		offset += 2;
		utf8Length = ::BigToHost16(&utf8Length);
		
		index = offset;
		while (utf8Length <= 0)
		{
			if (dataLen < index)
				return -1;
			start = *(pData+index);
			c1 = start >= 0x00 && start <= 0x7f;
			c2 = start >= 0xc2 && start <= 0xdf;
			c3 = start == 0xe0 || (start >= 0xe1 && start <= 0xec) || start == 0xed || (start >= 0xee && start <= 0xef);
			c4 = start == 0xf0 || (start >= 0xf1 && start <= 0xf3) || (start == 0xf4);

			if (c1)
				length = 1;
			else if (c2)
				length = 2;
			else if (c3)
				length = 3;
			else if (c4)
				length = 4;
			else 
				return -1;

			index += length;
			utf8Length--;
		}

		valueLen = index - offset;
		pValue = new char[valueLen];
		break;
	default:
		return 0;
		break;
	}

	memcpy(pValue,pData+offset,valueLen);
	offset += valueLen;

	pAmf->dataType = valueType;
	pAmf->pData = pValue;
	pAmf->dataLen = valueLen;

	return offset;
}

static int SplitCompositDataType(uint8_t *pData, const int dataLen)
{
	const uint8_t valueType = *pData;
	int offset = 0;
	char *pValue = NULL;
	int valueLen = 0;

	//object marker
	int index = 0;
	U16 utf8_length = 0;
	char start = 0x00;
	bool c1 = false, c2 = false, c3 = false, c4 = false;
	int string_count = 0;

	//ecma array marker
	U32 associative_count = 0;
	
	offset += 1;
	switch (valueType)
	{
	case OBJECT_MARKER:
		index = offset;
		while (1)
		{
			memcpy(&utf8_length,pData+index,2);
			index += 2;
			utf8_length = ::BigToHost16(&utf8_length);

			if (utf8_length == 0 && *(pData + index) == OBJECT_END_MARKER)
			{
				index += 1;
				break;
			}

			while (utf8_length > 0 )
			{
				start = *(pData+index);
				c1 = start >= 0x00 && start <= 0x7f;
				c2 = start >= 0xc2 && start <= 0xdf;
				c3 = start == 0xe0 || (start >= 0xe1 && start <= 0xec) || start == 0xed || (start >= 0xee && start <= 0xef);
				c4 = start == 0xf0 || (start >= 0xf1 && start <= 0xf3) || (start == 0xf4);

				if (c1)
					index += 1;
				else if (c2)
					index += 2;
				else if (c3)
					index += 3;
				else if (c4)
					index += 4;
				else
					return -1;
				utf8_length -- ;
			}

			string_count ++;
		}
		
		valueLen = index - offset;
		pValue = new char[valueLen];
		break;

	case NULL_MARKER:
		return offset;
		break;
	case UNDEFINED_MARKER:
		return offset;
		break;
	case REFERENCE_MARKER:
		valueLen = 2;
		pValue = new char[valueLen];
		break;
	case ECMA_ARRAY_MARKER:
		//待定

		break;
	case STRICT_ARRAY_MARKER:
		break;
	case DATE_MARKER:
		break;
	case LONG_STRING_MARKER:
		break;
	case XML_DOCUMENT_MARKER:
		break;
	case TYPE_OBJECT_MARKER:
		break;
	default:
		break;
	}


	
}

