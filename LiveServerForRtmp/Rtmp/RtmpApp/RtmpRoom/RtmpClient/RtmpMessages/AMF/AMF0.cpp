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
		delete[] (pAmf->data_utf8.buff);
		pAmf->data_utf8.buff = NULL;
		pAmf->data_utf8.buffLength = 0;
		break;
	case AMF0Type::OBJECT:
		for (i=0;i<pAmf->data_object.utf8Count;i++)
		{
			delete[] pAmf->data_object.pUtf8[i].buff;
			pAmf->data_object.pUtf8[i].buff = NULL;
			pAmf->data_object.pUtf8[i].buffLength = 0;
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
	auto it = m_Datas.begin();
	
	for (it=m_Datas.begin() ; it!= m_Datas.end(); it++)
	{
		
		::amf0_free(*it);
		*it = NULL;
	}
	m_Datas.clear();
}

CAMF0* CAMF0::CreateAMF0( uint8_t *pData, const int dataLen)
{
	CAMF0 *pamf = NULL;
	int length = 0;

	pamf = new CAMF0;
	length = pamf->Splite(pData,dataLen);
	if (length == 0)
		
	return NULL;
}

void CAMF0::Destroy()
{
	delete this;
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
		pAMF->data_num = ::BigToHostDouble(buff,buffLength);
		delete[] buff;	buff = NULL;
		offset += buffLength;
		break;

	case AMF0Type::BOOLEAN:
		if ( offset + 1> dataLen) return -1;
		pAMF->dType = AMF0Type::BOOLEAN;
		buffLength = 1;	

		buff = new char[buffLength];
		memcpy(buff, pData + offset, buffLength);
		pAMF->data_bool = *buff;

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
		pAMF->data_utf8.buff = new char[buffLength];
		memcpy(pAMF->data_utf8.buff, pData + offset, buffLength);
		pAMF->data_utf8.buffLength = buffLength;
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
	uint8_t *ptr = NULL , *start = NULL;
	vector<UTF8> utf8s;
	UTF8 utf8 ;
	int i; 
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
			
			start = ptr;
			while (utf8Length > 0)
			{
				c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
				c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
				c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
				c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || ((*ptr) == 0xf4);

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
				ptr += length;
				utf8Length -- ;
			}

			length = ptr - start;
			utf8.buff = new char[length];
			utf8.buffLength = length;
			memcpy(utf8.buff,start,length);
			utf8s.push_back(utf8);
		}

		pAMF->data_object.utf8Count = utf8s.size();
		pAMF->data_object.pUtf8 = new UTF8[pAMF->data_object.utf8Count];
		for (i = 0;i<utf8s.size();i++)
		{
			pAMF->data_object.pUtf8[i].buff = utf8s.at(i).buff;
			pAMF->data_object.pUtf8[i].buffLength = utf8s.at(i).buffLength;
		}
		offset += (ptr)-(pData + offset);
		break;

	case AMF0Type::NULL_MARKER:
		pAMF->dType = AMF0Type::NULL_MARKER;
		return offset;
		break;
	case AMF0Type::UNDEFINED:
		pAMF->dType = AMF0Type::UNDEFINED;
		return offset;
		break;
	case AMF0Type::REFERENCE:
		pAMF->dType = AMF0Type::REFERENCE;
		buffLength = 2;
		buff = new char[buffLength];
		memcpy(buff,pData+offset,buffLength);

		pAMF->data_reference = ::BigToHost16(buff);

		delete[] buff; buff = NULL;

		offset += buffLength;
		break;
	case AMF0Type::ECMA_ARRAY:
		//待定
		pAMF->dType = AMF0Type::ECMA_ARRAY;
		

		break;
	case AMF0Type::STRICT_ARRAY:
		//待定
		pAMF->dType = AMF0Type::STRICT_ARRAY;
		
		break;
	case AMF0Type::DATE:
		//待定
		pAMF->dType = AMF0Type::DATE;
		
		break;
	case AMF0Type::LONG_STRING:
		//待定
		pAMF->dType = AMF0Type::LONG_STRING;
		break;
	case AMF0Type::XML_DOCUMENT:
		//待定
		pAMF->dType = AMF0Type::XML_DOCUMENT;
		break;
	case AMF0Type::TYPE_OBJECT:
		//待定
		pAMF->dType = AMF0Type::TYPE_OBJECT;
		break;
	default:
		amf0_free(pAMF);
		return 0;
		break;
	}

	m_Datas.push_back(pAMF);

	return offset;
}