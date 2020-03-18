#include "AMF0.h"

static AMF0Data* amf0_alloc()
{
	AMF0Data *pamf = NULL;

	pamf = new AMF0Data;
	memset(pamf, 0, sizeof(AMF0Data));
	return pamf;
}

static void amf0_free(AMF0Data *pAmf)
{
	int i = 0;
	switch (pAmf->dType)
	{
	case AMF0Type::NUMBER:
		break;
	case AMF0Type::BOOLEAN:
		break;
	case AMF0Type::STRING:
		delete[] (pAmf->data2.buff);
		pAmf->data2.buff = NULL;
		pAmf->data2.buffLength = 0;
		break;
	case AMF0Type::OBJECT:
		for (i=0;i<pAmf->data3.utf8Count;i++)
		{
			delete[] pAmf->data3.pUtf8[i].buff;
			pAmf->data3.pUtf8[i].buff = NULL;
			pAmf->data3.pUtf8[i].buffLength = 0;
		}
		break;
	case AMF0Type::MOVIECLIP:
		break;
	case AMF0Type::NULL_MARKER:
		break;
	case AMF0Type::UNDEFINED:
		break;
	case AMF0Type::REFERENCE:
		break;
	case AMF0Type::ECMA_ARRAY:
		break;
	case AMF0Type::OBJECT_END:
		break;
	case AMF0Type::STRICT_ARRAY:
		break;
	case AMF0Type::DATE:
		break;
	case AMF0Type::LONG_STRING:
		break;
	case AMF0Type::UNSUPPORTED:
		break;
	case AMF0Type::RECORDSET:
		break;
	case AMF0Type::XML_DOCUMENT:
		break;
	case AMF0Type::TYPE_OBJECT:
		break;

	default:
		break;
	}

	delete pAmf;
	return;
}

CAMF0::CAMF0()
{

}

CAMF0::~CAMF0()
{

}

CAMF0* CAMF0::CreateAMF0( uint8_t *pData, const int dataLen)
{
	CAMF0 *pamf = NULL;
	int length = 0;

	pamf = new CAMF0;
	length = pamf->Splite(pData,dataLen);
	return NULL;
}

int CAMF0::Splite(uint8_t *pData, const int dataLen)
{

}

int CAMF0::SpliteBasicType(uint8_t *pData, const int dataLen)
{
	const uint8_t valueType = *pData;
	AMF0Data *pAMF = ::amf0_alloc();
	int offset = 0;
	char *buff = NULL; 
	int buffLength = 0;
	
	//string
	uint16_t utf8Length = 0;
	int length = 0;
	uint8_t  start = 0x00;
	uint8_t *ptr = NULL;
	bool c1 = false, c2 = false, c3 = false, c4 = false;

	offset += 1;
	switch (valueType)
	{
	case AMF0Type::NUMBER:
		if (offset+8 > dataLen)	return -1;
		
		pAMF->dType = AMF0Type::NUMBER;
		buffLength = 8;
		buff = new char[buffLength];
		memcpy(buff,pData+offset,buffLength);
		pAMF->data0 = ::BigToHostDouble(buff,buffLength);
		delete[] buff;	buff = NULL;
		offset += buffLength;
		break;

	case AMF0Type::BOOLEAN:
		if ( offset + 1> dataLen) return -1;
		pAMF->dType = AMF0Type::BOOLEAN;
		buffLength = 1;	

		buff = new char[buffLength];
		memcpy(buff, pData + offset, buffLength);
		pAMF->data1 = *buff;

		delete[] buff; buff = NULL;	
		offset += buffLength;
		break;

	case AMF0Type::STRING:
		if (offset + 2 > dataLen) return -1;

		pAMF->dType = AMF0Type::STRING;
		memcpy(&utf8Length,pData+offset,2);
		utf8Length = BigToHost16(&utf8Length);
		offset += 2;

		ptr = (pData + offset);
		while (utf8Length > 0)
		{
			start = *(ptr);
			c1 = start >= 0x00 && start <= 0x7f;
			c2 = start >= 0xc2 && start <= 0xdf;
			c3 = start == 0xe0 || (start >= 0xe1 && start <= 0xec) || start == 0xed || (start >= 0xee && start <= 0xef);
			c4 = start == 0xf0 || (start >= 0xf1 && start <= 0xf3) || (start == 0xf4);

			if (c1)
				length = 1;
			else if (c2)
				length = 2 ;
			else if (c3)
				length = 3;
			else if (c4)
				length = 4;
			else 
				return -1;

			ptr += length;
			utf8Length --;
		}

		buffLength = ptr - (pData + offset);
		pAMF->data2.buff = new char[buffLength];
		memcpy(pAMF->data2.buff, pData + offset, buffLength);
		pAMF->data2.buffLength = buffLength;
		break;

	default:
		amf0_free(pAMF);
		pAMF = NULL;
		return 0;
		break;
	}

	m_Datas.push_back(pAMF);
	return offset;
}

int CAMF0::SpliteCompositType(uint8_t *pData, const int dataLen)
{
	const uint8_t valueType = *pData;
	AMF0Data *pAMF = ::amf0_alloc();
	int offset = 0;
	char *buff = NULL;
	int buffLength = 0;

	//object
	uint16_t utf8Length = 0;
	int		utf8Count = 0;
	uint8_t *ptr = NULL;
	uint8_t  start = 0x00;
	bool c1 = false, c2 = false, c3 = false, c4 = false;
	int length = 0;
	
	offset += 1;
	switch (valueType)
	{
	case AMF0Type::OBJECT:
		pAMF->dType = AMF0Type::OBJECT;

		ptr = pData + offset;
		while (1)
		{
			memcpy(&utf8Length, ptr, 2);
			utf8Length = BigToHost16(&utf8Length);
			ptr += 2;
			
			if (utf8Length == 0 && *ptr == AMF0Type::OBJECT_END)
				break;

			while (utf8Length > 0)
			{
				start = *(ptr);
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
				ptr += length;
				utf8Length -- ;
			}
			utf8Count ++;
		}

		pAMF->data3.utf8Count = utf8Count;
		pAMF->data3.pUtf8 = new UTF8[utf8Count];



		break;

	case AMF0Type::NULL_MARKER:
		return offset;
		break;
	case AMF0Type::UNDEFINED:
		return offset;
		break;
	case AMF0Type::REFERENCE:
	
		break;
	case AMF0Type::ECMA_ARRAY:
		//´ý¶¨

		break;
	case AMF0Type::STRICT_ARRAY:
		break;
	case AMF0Type::DATE:
		break;
	case AMF0Type::LONG_STRING:
		break;
	case AMF0Type::XML_DOCUMENT:
		break;
	case AMF0Type::TYPE_OBJECT:
		break;
	default:
		break;
	}

}