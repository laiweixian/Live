#include "AMF0.h"

void UTF8_free(UTF8 &utf8)
{
	if (utf8.buff)	delete[] utf8.buff;
	utf8.buff = NULL;
	utf8.buffLength = 0;
}

void AMF0Object_free(AMF0Object &amfObject)
{
	int i = 0;
	for (i = 0;i < amfObject.utf8Count;i++)
		UTF8_free(amfObject.pUtf8s[i]);

	if (amfObject.pUtf8s)	delete[] amfObject.pUtf8s;
	amfObject.pUtf8s = NULL;
	amfObject.utf8Count = 0;
}

void AMF0EcmaArray_free(AMF0EcmaArray &ecma)
{
	int i = 0;
	for (i = 0;i < ecma.objCount;i++)
		AMF0Object_free(ecma.pObjects[i]);

	if (ecma.pObjects)	delete[] ecma.pObjects;
	ecma.pObjects = NULL;
	ecma.objCount = 0;
}

void AMF0StrictArray_free(AMF0StrictArray &strict)
{
	int i = 0;
	for (i=0;i<strict.amfDataCount;i++)
		AMF0Data_free(strict.pAMFData[i]);
	if (strict.pAMFData)	delete[] strict.pAMFData;
	strict.pAMFData = NULL;
	strict.amfDataCount = 0;
}

void AMF0TypeObject_free(AMF0TypeObject& typeObject)
{
	int i = 0;
	for (i=0;i<typeObject.objCount;i++)
		AMF0Object_free(typeObject.pObjects[i]);
	UTF8_free(typeObject.className);
	if (typeObject.pObjects)	delete[] typeObject.pObjects;
	typeObject.pObjects = NULL;
	typeObject.objCount = 0;
}
void AMF0Data_free(AMF0Data &amfData)
{
	switch (amfData.dType)
	{
	case AMF0Type::NUMBER:
		break;
	case AMF0Type::BOOLEAN:
		break;
	case AMF0Type::STRING:
		UTF8_free(amfData.data_utf8);
		break;
	case AMF0Type::OBJECT:
		AMF0Object_free(amfData.data_object);
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
		AMF0EcmaArray_free(amfData.data_ecma_array);
		break;
	case AMF0Type::OBJECT_END:
		break;
	case AMF0Type::STRICT_ARRAY:
		AMF0StrictArray_free(amfData.data_strict_array);
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
		AMF0TypeObject_free(amfData.data_type_object);
		break;

	default:
		break;
	}
}

AMF0Data* amf0_init()
{
	AMF0Data *pamf = NULL;

	pamf = new AMF0Data;
	memset(pamf, 0, sizeof(AMF0Data));
	return pamf;
}

void amf0_free(AMF0Data **pamf)
{
	AMF0Data_free(**pamf);
	delete *pamf;
	*pamf = NULL;
	return ;
}

CAMF0::CAMF0()
{

}

CAMF0::~CAMF0()
{
	auto it = m_Datas.begin();
	
	for (it=m_Datas.begin() ; it!= m_Datas.end(); it++)
		::amf0_free(&(*it));
	m_Datas.clear();
}

CAMF0* CAMF0::CreateAMF0( uint8_t *pData, const int dataLen)
{
	CAMF0 *pamf = NULL;
	int ret  = 0;
	int offset = 0;
	int length = 0;

	pamf = new CAMF0;
	while (1)
	{
		length = pamf->Splite(pData+offset,dataLen-offset);
		if (length == 0)
			break;
		if (length == -1)
		{
			pamf->Destroy();
			pamf = NULL;
			break;
		}
		offset += length;
	}

	return pamf;
}

void CAMF0::Destroy()
{
	delete this;
}

int CAMF0::Splite( uint8_t *pData, const int dataLen)
{
	AMF0Data *amf = amf0_init();
	int length  = 0;

	if (dataLen == 0)
		return 0;

	length = SpliteBasicType(pData,dataLen,amf);
	if (length == -1)
		return -1;
	if (length == 0)
		length = SpliteCompositType(pData,dataLen,amf);

	if (length == -1)
		return -1;
	if (length == 0)
		return -1;

	m_Datas.push_back(amf);

	return length;
}

int CAMF0::SpliteBasicType( uint8_t *pData, const int dataLen, AMF0Data *pAMF)
{
	const uint8_t valueType = *pData;
	char *buff = NULL; 
	int buffLength = 0;
	int offset = 0;
	
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
		pAMF->dType = AMF0Type::NUMBER;
		buffLength = 8;
		buff = new char[buffLength];
		memcpy(buff,ptr,buffLength);
		pAMF->data_num = ::BigToHostDouble(buff,buffLength);
		delete[] buff;	buff = NULL;
		offset += buffLength;
		break;

	case AMF0Type::BOOLEAN:
		pAMF->dType = AMF0Type::BOOLEAN;
		buffLength = 1;	
		buff = new char[buffLength];
		memcpy(buff, pData + offset, buffLength);
		pAMF->data_bool = *buff;

		delete[] buff; buff = NULL;	
		offset += buffLength;
		break;

	case AMF0Type::STRING:
		pAMF->dType = AMF0Type::STRING;
		memcpy(&utf8Length,pData+offset,2);
		utf8Length = BigToHost16(&utf8Length);
		offset += 2;

		ptr = pData + offset;
		while (utf8Length > 0)
		{
			start = *ptr;
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

		buffLength = ptr - (pData+offset);
		pAMF->data_utf8.buff = new char[buffLength];
		memcpy(pAMF->data_utf8.buff, pData + offset, buffLength);
		pAMF->data_utf8.buffLength = buffLength;

		offset += buffLength;
		break;
	case AMF0Type::UNDEFINED:
		pAMF->dType = AMF0Type::UNDEFINED;
		break;
	case AMF0Type::NULL_MARKER:
		pAMF->dType = AMF0Type::NULL_MARKER;
		break;
	default:
		return 0;
		break;
	}

	return offset;
}

int CAMF0::SpliteCompositType(uint8_t *pData, const int dataLen,AMF0Data *pAMF)
{
	const uint8_t valueType = *pData;
	int offset = 0;
	char *buff = NULL;
	int buffLength = 0;

	//object
	uint8_t *ptr = NULL,*utf8Start = NULL;
	char endMarker[3] = {0};
	uint16_t utf8Length = 0;
	vector<UTF8> utf8Str;
	int i;
	bool c1 = false, c2 = false, c3 = false, c4 = false;
	int length = 0;

	//ECMA ARRAY
	uint32_t associative_count = 0;
	AMF0Data *ecma = NULL;
	int objectLength = 0;

	offset += 1;
	switch (valueType)
	{
	case AMF0Type::OBJECT:
		pAMF->dType = AMF0Type::OBJECT;

		ptr = (pData + offset);
		while (1)
		{
			memcpy(endMarker,ptr,3);
			if (endMarker[0] == 0x00 && endMarker[1] == 0x00 && endMarker[2] == OBJECT_END)
			{
				ptr += 3;
				break;
			}

			memcpy(&utf8Length, ptr, 2);
			utf8Length = BigToHost16(&utf8Length);
			ptr += 2;

			utf8Start = ptr;
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
				utf8Length --;
			}

			buffLength = ptr - utf8Start;
			buff = new char[buffLength];
			memcpy(buff,utf8Start,buffLength);
			utf8Str.push_back({buff,buffLength});
		}

		pAMF->data_object.utf8Count = utf8Str.size();
		pAMF->data_object.pUtf8s = new UTF8[utf8Str.size()];
		for (i=0;i<utf8Str.size();i++)
			pAMF->data_object.pUtf8s[i] = utf8Str.at(i);
		
		offset += ptr - (pData-offset);
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
		
		ptr = pData + offset;
		memcpy(&associative_count,ptr,4);
		associative_count = ::BigToHost32(&associative_count);
		ptr += 4;

		pAMF->data_ecma_array.objCount = associative_count;
		pAMF->data_ecma_array.pObjects  = new AMF0Object[associative_count];
		i = 0;
		while (associative_count > 0)
		{
			ecma = amf0_init();
			objectLength = SpliteCompositType(ptr,pData+dataLen-ptr, ecma);
			if (objectLength == 0 || objectLength == -1 || ecma->dType != AMF0Type::OBJECT)
				return -1;
			
			ptr += objectLength;

			pAMF->data_ecma_array.pObjects[i] = ecma->data_object;
			i++;
			associative_count --;
		}

		offset += ptr - (pData+offset);

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
		return 0;
		break;
	}

	return offset;
}