#include "AMF0.h"

#define CHECK_OFFSET(start,end,ptr,off)	\
	if (ptr + off > end )	return OUT_OF_DATA;

void UTF8_free(UTF8 &utf8)
{
	if (utf8.buff)	delete[] utf8.buff;
	utf8.buff = NULL;
	utf8.buffLength = 0;
}

void AMF0Object_free(AMF0Object &amfObject)
{
	int i = 0;
	for (i = 0;i < amfObject.objCount;i++)
	{
		UTF8_free(amfObject.pObjs[i].name);
		AMF0Data_free(amfObject.pObjs[i].data);
	}

	if(amfObject.pObjs)
		delete[] amfObject.pObjs;
	amfObject.pObjs = NULL;
	amfObject.objCount = 0;
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
	pamf->dType = AMF0Type::INVALID;
	return pamf;
}

void amf0_free(AMF0Data **pamf)
{
	if (*pamf == NULL)
		return;
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


	return pamf;
}

void CAMF0::Destroy()
{
	delete this;
}
int Splite(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{
	if (pData == NULL || dataLen == 0 || pAMF->dType != AMF0Type::INVALID)
		return INVALID_INPUT_ARGS;

	int ret = SAR_FAILURE;
	uint8_t marker = 0x00;
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	CHECK_OFFSET(start, end, ptr, 1)
	marker = *ptr;
	ptr += 1;
	switch (marker)
	{
	case AMF0Type::NUMBER:
		 break;
	case AMF0Type::BOOLEAN:
		break;
	case AMF0Type::STRING:
		break;
	case AMF0Type::OBJECT:
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

}

int CAMF0::SpliteBasicType( uint8_t *pData, const int dataLen, AMF0Data *pAMF,int *outLen)
{
	if (pData == NULL || dataLen == 0 || pAMF->dType != AMF0Type::INVALID)
		return INVALID_INPUT_ARGS;

	int ret = SAR_FAILURE;

	uint8_t marker = 0x00;
	uint8_t *ptr = pData;
	const uint8_t* start = pData , *end = pData + dataLen;
	
	

	//number
	DOUBLE num = 0;

	//boolean
	uint8_t booleanData = 0x00; 

	//string
	uint8_t *utf8 = NULL;
	int utf8Len = 0;
	int utf8Offset = 0;
	

	CHECK_OFFSET(start,end,ptr,1)
	marker = *ptr;
	ptr += 1;
	switch (marker)
	{
	case AMF0Type::NUMBER:
		CHECK_OFFSET(start, end, ptr, 8)
		::memcpy(&num,ptr,8);
		ptr += 8;

		pAMF->dType = AMF0Type::NUMBER;
		pAMF->data_num = ::BigToHostDouble(&num, sizeof(DOUBLE));
		break;

	case AMF0Type::BOOLEAN:
		CHECK_OFFSET(start, end, ptr,  1)
		booleanData = *ptr;
		ptr += 1;

		pAMF->dType = AMF0Type::BOOLEAN;
		pAMF->data_bool = booleanData;
		break;

	case AMF0Type::STRING:
		ret = CAMF0::ParseUTF8(ptr,end-ptr, NULL,&utf8Len,&utf8Offset);
		if (ret != SAR_OK)
			return ret;

		utf8 = new uint8_t[utf8Len];
		ret = CAMF0::ParseUTF8(ptr,end-ptr,utf8,&utf8Len,&utf8Offset);
		ptr += utf8Offset;

		pAMF->dType = AMF0Type::STRING;
		pAMF->data_utf8.buff = utf8;
		pAMF->data_utf8.buffLength = utf8Len;
		break;
	case AMF0Type::UNDEFINED:
		pAMF->dType = AMF0Type::UNDEFINED;
		pAMF->data_reserved = NULL;
		break;
	case AMF0Type::NULL_MARKER:
		pAMF->dType = AMF0Type::NULL_MARKER;
		pAMF->data_reserved = NULL;
		break;
	default:
		*outLen = 0;
		return NO_THIS_TYPE;
		break;
	}

	*outLen = ptr - start;
	return SAR_OK;
}


int CAMF0::ParseNumber(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	DOUBLE num = 0;

	CHECK_OFFSET(start,end,ptr,8);
	memcpy(&num,ptr,8);
	ptr += 8;

	*outOffset = ptr - start; 
	pAMF->dType = AMF0Type::NUMBER;
	pAMF->data_num = BigToHostDouble(&num,sizeof(DOUBLE));
	return SAR_OK;
}

int CAMF0::ParseBoolean(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	uint8_t boolData = 0x00;

	CHECK_OFFSET(start,end,ptr,1)
	memcpy(&boolData,ptr,1);
	ptr += 1;

	*outOffset = ptr - start;
	pAMF->dType = AMF0Type::BOOLEAN;
	pAMF->data_bool = boolData;
	return SAR_OK;
}
int CAMF0::ParseString(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	int ret = SAR_FAILURE;
	uint8_t *utf8 = NULL;
	int utf8Length = 0;
	int offset = 0;

	ret = CAMF0::ParseUTF8(ptr,end-ptr,NULL,&utf8Length,&offset);
	if (ret != SAR_OK)
		return ret ;

	utf8 = new uint8_t[utf8Length];
	ret = CAMF0::ParseUTF8(ptr, end - ptr, utf8, &utf8Length, &offset);
	ptr += offset;

	*outOffset = ptr - start;
	pAMF->dType = AMF0Type::STRING;
	pAMF->data_utf8.buff = new uint8_t[utf8Length];
	pAMF->data_utf8.buffLength = utf8Length;
	return SAR_OK;
}
int CAMF0::ParseObject(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	
	int ret = SAR_FAILURE;
	uint8_t three[3] = {0};
	int utf8BuffLength;
	int offset = 0;
	int i = 0;
	vector<AMF0Obj> objs;
	AMF0Obj obj;
	AMF0Data *pValue = NULL;
	
	while (1)
	{
		CHECK_OFFSET(start,end,ptr,3)
		memcpy(three,ptr,3);
		if (three[0] == 0x00 && three[1] == 0x00 && three[2] == AMF0Type::OBJECT_END)
		{
			ptr += 3;
			break;
		}

		ret = CAMF0::ParseUTF8(ptr,end-ptr,NULL,&utf8BuffLength,&offset);
		if (ret != SAR_OK)
			goto PARSE_ERR;

		obj.name.buff = new uint8_t[utf8BuffLength];
		obj.name.buffLength = utf8BuffLength;
		ret = CAMF0::ParseUTF8(ptr, end - ptr, obj.name.buff, &utf8BuffLength, &offset);
		ptr += offset;


		//
		offset = 0;
		pValue = amf0_init();
		ret = Splite(ptr,end-ptr,pValue,&offset);
		if (ret != SAR_OK)
			goto PARSE_ERR;
		
		ptr += offset;
		obj.data = *pValue;
		objs.push_back(obj);
	}

	pAMF->dType = AMF0Type::OBJECT;
	pAMF->data_object.objCount = objs.size();
	pAMF->data_object.pObjs = new AMF0Obj[objs.size()];
	for (i=0;i<objs.size(); i++)
		pAMF->data_object.pObjs[i] = objs.at(i);
	
	*outOffset = ptr - start;
	return SAR_OK;

PARSE_ERR:
	for (i = 0;i<objs.size(); i++)
	{
		AMF0Data_free(objs.at(i).data);
		UTF8_free(objs.at(i).name);
	}
	objs.clear();
	return ret;
}
int CAMF0::ParseMovieClip(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseNull(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseUndefined(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseReference(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseEcmaArray(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseObjectEnd(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseStrictArray(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseDate(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseLongString(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseUnsupported(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseRecordSet(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseXmlDocument(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}
int CAMF0::ParseTypeObject(uint8_t *pData, const int dataLen, AMF0Data *pAMF, int* outOffset)
{

}

int CAMF0::ParseUTF8(uint8_t *pData, const int dataLen, uint8_t* utf8, int *outUtf8Length,int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	uint16_t utf8CharCount = 0;
	int i = 0;
	bool c1 =false , c2 = false, c3 = false, c4 = false;
	int utf8CharLength = 0;

	uint8_t *utf8Buff = NULL;
	int utf8BuffLen =  0;

	CHECK_OFFSET(start,end,ptr,2)
	memcpy(&utf8CharCount,ptr,2);
	ptr += 2;

	i = utf8CharCount; 
	while (i > 0)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr)<= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr)>= 0xf1 && (*ptr) <= 0xf3 ) || (*ptr) == 0xf4;

		if(c1)
			utf8CharLength = 1;
		else if (c2)
			utf8CharLength = 2;
		else if (c3)
			utf8CharLength = 3;
		else if (c4)
			utf8CharLength = 4;
		else 
			return INVALID_UTF8_CHAR;

		CHECK_OFFSET(start,end,ptr,utf8CharLength)
		ptr += utf8CharLength;
		i--;	
	}

	utf8BuffLen = ptr - start - 2;
	utf8Buff = new uint8_t[utf8BuffLen];
	memcpy(utf8Buff,start+2,utf8BuffLen);

	*outUtf8Length = utf8BuffLen;
	*outOffset = ptr - start;
	if (utf8 != NULL)
		memcpy(utf8,utf8Buff,utf8BuffLen);

	return SAR_OK;
}

int CAMF0::ParseUTF8Long(uint8_t *pData, const int dataLen, uint8_t* outChar, int *outCharLen)
{

}