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
		UTF8_free(amfData.data_string);
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
		UTF8_free(amfData.data_string_long);
		break;
	case AMF0Type::UNSUPPORTED:
		break;
	case AMF0Type::RECORDSET:
		break;
	case AMF0Type::XML_DOCUMENT:
		UTF8_free(amfData.data_xml_document);
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
	auto it = m_Amfs.begin();
	
	for (it= m_Amfs.begin() ; it!= m_Amfs.end(); it++)
		::amf0_free(&(*it));
	m_Amfs.clear();
}

CAMF0* CAMF0::CreateAMF0( uint8_t *pData, const int dataLen)
{
	CAMF0 *pamf = NULL;
	int ret ;
	pamf = new CAMF0;
	
	ret = pamf->Init(pData,dataLen);
	if (ret != SAR_OK)
	{
		pamf->Destroy();
		pamf = NULL;
	}
	return pamf;
}

void CAMF0::Destroy()
{
	delete this;
}

int CAMF0::Init(uint8_t *pData, const int dataLen)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	int offset = 0;

	AMF0Data *amf = NULL;

	while (ptr < end)
	{
		amf = CAMF0::Splite(ptr,end-ptr,&offset);
		if (amf == NULL)
			return SAR_FAILURE;
		ptr += offset;
		m_Amfs.push_back(amf);
	}
	return SAR_OK;
}

AMF0Data* CAMF0::Splite(uint8_t *pData, const int dataLen, int* outOffset)
{
	if (pData == NULL || dataLen == 0 )
		return NULL;

	uint8_t marker = 0x00;
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	int ret = SAR_FAILURE;
	int offset = 0;
	AMF0Type amfType = AMF0Type::INVALID;
	AMF0Data* pamf = amf0_init();
	
	marker = *ptr;
	ptr += 1;
	switch (marker)
	{
	case AMF0Type::NUMBER:
		amfType = AMF0Type::NUMBER;
		ret = CAMF0::ParseNumber(ptr,end-ptr,pamf->data_num,&offset);
		break;
	case AMF0Type::BOOLEAN:
		amfType = AMF0Type::BOOLEAN;
		ret = CAMF0::ParseBoolean(ptr, end - ptr, pamf->data_bool, &offset);
		break;
	case AMF0Type::STRING:
		amfType = AMF0Type::STRING;
		ret = CAMF0::ParseString(ptr,end-ptr,pamf->data_string,&offset);
		break;
	case AMF0Type::OBJECT:
		amfType = AMF0Type::OBJECT;
		ret = CAMF0::ParseObject(ptr,end-ptr,pamf->data_object,&offset);
		break;
	case AMF0Type::MOVIECLIP:
		amfType = AMF0Type::MOVIECLIP;
		ret = CAMF0::ParseMovieClip(ptr,end-ptr,&offset);
		break;
	case AMF0Type::NULL_MARKER:
		amfType = AMF0Type::NULL_MARKER;
		ret = CAMF0::ParseNull(ptr,end-ptr,&offset);
		break;
	case AMF0Type::UNDEFINED:
		amfType = AMF0Type::UNDEFINED;
		ret = CAMF0::ParseUndefined(ptr,end-ptr,&offset);
		break;
	case AMF0Type::REFERENCE:
		amfType = AMF0Type::REFERENCE;
		ret = CAMF0::ParseReference(ptr,end-ptr,pamf->data_reference,&offset);
		break;
	case AMF0Type::ECMA_ARRAY:
		amfType = AMF0Type::ECMA_ARRAY;
		ret = CAMF0::ParseEcmaArray(ptr,end-ptr,pamf->data_ecma_array,&offset);
		break;
	case AMF0Type::OBJECT_END:
		amfType = AMF0Type::OBJECT_END;
		ret = CAMF0::ParseObjectEnd(ptr,end-ptr,&offset);
		break;
	case AMF0Type::STRICT_ARRAY:
		amfType = AMF0Type::STRICT_ARRAY;
		ret = CAMF0::ParseStrictArray(ptr,end-ptr,pamf->data_strict_array,&offset);
		break;
	case AMF0Type::DATE:
		amfType = AMF0Type::DATE;
		ret = CAMF0::ParseDate(ptr,end-ptr,pamf->data_date,&offset);
		break;
	case AMF0Type::LONG_STRING:
		amfType = AMF0Type::LONG_STRING;
		ret = CAMF0::ParseLongString(ptr,end-ptr,pamf->data_string_long,&offset);
		break;
	case AMF0Type::UNSUPPORTED:
		amfType = AMF0Type::UNSUPPORTED;
		ret = CAMF0::ParseUnsupported(ptr,end-ptr,&offset);
		break;
	case AMF0Type::RECORDSET:
		amfType = AMF0Type::RECORDSET;
		ret = CAMF0::ParseRecordSet(ptr,end-ptr,&offset);
		break;
	case AMF0Type::XML_DOCUMENT:
		amfType = AMF0Type::XML_DOCUMENT;
		ret = CAMF0::ParseXmlDocument(ptr,end-ptr,pamf->data_xml_document,&offset);
		break;
	case AMF0Type::TYPE_OBJECT:
		amfType = AMF0Type::TYPE_OBJECT;
		ret = CAMF0::ParseTypeObject(ptr,end-ptr,pamf->data_type_object,&offset);
		break;
	default:
		break;
	}
	ptr += offset;
	
	if (ret != SAR_OK)
	{
		amf0_free(&pamf);
		*outOffset = 0;
		return NULL;
	}

	*outOffset = ptr - start;
	return pamf;
}



int CAMF0::ParseNumber(uint8_t *pData, const int dataLen, DOUBLE& number, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	DOUBLE num = 0;

	CHECK_OFFSET(start,end,ptr,8);
	memcpy(&num,ptr,8);
	ptr += 8;

	*outOffset = ptr - start; 
	number = BigToHostDouble(&num,sizeof(DOUBLE));
	return SAR_OK;
}

int CAMF0::ParseBoolean(uint8_t *pData, const int dataLen, U8& boolData, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	uint8_t boolD = 0x00;

	CHECK_OFFSET(start,end,ptr,1)
	memcpy(&boolD,ptr,1);
	ptr += 1;

	*outOffset = ptr - start;
	boolData = boolD;
	return SAR_OK;
}

int CAMF0::ParseString(uint8_t *pData, const int dataLen, UTF8& utf8, int* outOffset)
{
	return CAMF0::ParseUTF8(pData,dataLen,utf8,outOffset);
}

int CAMF0::ParseObject(uint8_t *pData, const int dataLen, AMF0Object& amfObj, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	
	int ret = SAR_FAILURE;
	uint8_t three[3] = {0};
	int offset = 0;
	int i = 0;
	
	AMF0Data *pValue = NULL;
	vector<Obj> objs;
	Obj obj;
	UTF8 name; 
	
	while (1)
	{
		CHECK_OFFSET(start,end,ptr,3)
		memcpy(three,ptr,3);
		if (three[0] == 0x00 && three[1] == 0x00 && three[2] == AMF0Type::OBJECT_END)
		{
			ptr += 3;
			break;
		}

		ret = CAMF0::ParseUTF8(ptr,end-ptr,name,&offset);
		if (ret != SAR_OK)
			goto PARSE_ERR;
		ptr += offset;


		pValue = CAMF0::Splite(ptr,end-ptr,&offset);
		if (pValue == NULL)
			goto PARSE_ERR;
		ptr += offset;

		obj.name = name;
		obj.data = *pValue;
		objs.push_back(obj);
	}

	amfObj.objCount = objs.size();
	amfObj.pObjs = new Obj[objs.size()];
	for (i=0;i<objs.size();i++)
		amfObj.pObjs[i] = objs.at(i);
	*outOffset = ptr - start;

	return SAR_OK;

PARSE_ERR:
	for (i = 0;i<objs.size(); i++)
	{
		AMF0Data_free(objs.at(i).data);
		UTF8_free(objs.at(i).name);
	}
	objs.clear();
	*outOffset = 0;
	return ret;
}

int CAMF0::ParseMovieClip(uint8_t *pData, const int dataLen,  int* outOffset)
{
	return SAR_FAILURE;
}

int CAMF0::ParseNull(uint8_t *pData, const int dataLen, int* outOffset)
{
	*outOffset = 0;
	return SAR_OK;
}

int CAMF0::ParseUndefined(uint8_t *pData, const int dataLen,  int* outOffset)
{
	*outOffset = 0;
	return SAR_OK;
}

int CAMF0::ParseReference(uint8_t *pData, const int dataLen, U16 &refer, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	uint16_t indexPoint = 0;

	CHECK_OFFSET(start,end,ptr,2)
	memcpy(&indexPoint,ptr,2);
	ptr += 2;

	refer = ::BigToHost16(&indexPoint);
	*outOffset = ptr - start;

	return SAR_OK;
}

int CAMF0::ParseEcmaArray(uint8_t *pData, const int dataLen, AMF0EcmaArray &ecma, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	uint32_t associative_count  = 0;
	int i = 0;

	int ret = SAR_FAILURE;
	int offset = 0;
	AMF0Object obj;
	uint8_t marker = 0x00;

	CHECK_OFFSET(start,end,ptr,4)
	memcpy(&associative_count,ptr,4);
	ptr += 4;

	associative_count = ::BigToHost32(&associative_count);
	
	ecma.objCount = associative_count;
	ecma.pObjects = new AMF0Object[associative_count];
	i = associative_count;
	while (i>0)
	{
		
		CHECK_OFFSET(start,end,ptr,1)
		marker = *ptr;
		ptr += 1;

		ret = CAMF0::ParseObject(ptr,end-ptr,ecma.pObjects[i],&offset);
		if (ret != SAR_OK)
			goto PARSE_ERR;
		ptr += offset;
		i--;
	}
	
	*outOffset = ptr - start;
	return SAR_OK;

PARSE_ERR:

	return ret; 

}

int CAMF0::ParseObjectEnd(uint8_t *pData, const int dataLen, int* outOffset)
{
	return SAR_FAILURE;
}

int CAMF0::ParseStrictArray(uint8_t *pData, const int dataLen, AMF0StrictArray& strictArray, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	int ret = SAR_FAILURE;
	int offset;

	//
	uint32_t array_count = 0;
	int i = 0;
	AMF0Data *pValue = NULL;

	CHECK_OFFSET(start,end,ptr,4)
	memcpy(&array_count,ptr,4);
	ptr += 4;

	array_count = ::BigToHost32(&array_count);

	strictArray.amfDataCount = array_count;
	strictArray.pAMFData = new AMF0Data[array_count];
	i = array_count;
	while (i > 0)
	{
		pValue = Splite(ptr,end-ptr,&offset);
		if (pValue == NULL)
			goto PARSE_ERR;
		ptr += offset;

		strictArray.pAMFData[i] = *pValue;
		i--;
	}

	return SAR_OK;

PARSE_ERR:

	return ret;
}

int CAMF0::ParseDate(uint8_t *pData, const int dataLen, DOUBLE& date, int* outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;
	int ret = SAR_FAILURE;

	DOUBLE dateData = 0;
	S16 timeZone = 0;

	CHECK_OFFSET(start,end,ptr,8)
	memcpy(&dateData,ptr,8);
	ptr += 8;

	CHECK_OFFSET(start,end,ptr,2)
	memcpy(&timeZone,ptr,2);
	ptr += 2;

	date = ::BigToHostDouble(&dateData,8);
	*outOffset = ptr - start;
	return SAR_OK;
}

int CAMF0::ParseLongString(uint8_t *pData, const int dataLen, UTF8 &utf8, int* outOffset)
{
	return CAMF0::ParseUTF8Long(pData,dataLen,utf8,outOffset);
}

int CAMF0::ParseUnsupported(uint8_t *pData, const int dataLen, int* outOffset)
{
	return SAR_FAILURE;
}

int CAMF0::ParseRecordSet(uint8_t *pData, const int dataLen, int* outOffset)
{
	return SAR_FAILURE;
}

int CAMF0::ParseXmlDocument(uint8_t *pData, const int dataLen, UTF8 &utf8, int* outOffset)
{
	return CAMF0::ParseUTF8Long(pData, dataLen, utf8, outOffset);
}

int CAMF0::ParseTypeObject(uint8_t *pData, const int dataLen, AMF0TypeObject &typeObject, int* outOffset)
{
	//标准文档完全不明(原因:object-property数组没有结束标志)
	return SAR_FAILURE;
}

int CAMF0::ParseUTF8(uint8_t *pData, const int dataLen, UTF8& utf8, int *outOffset)
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

	utf8CharCount = ::BigToHost16(&utf8CharCount);
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

	*outOffset = ptr - start;
	utf8.buff = utf8Buff;
	utf8.buffLength = utf8BuffLen;
	return SAR_OK;
}

int CAMF0::ParseUTF8Long(uint8_t *pData, const int dataLen, UTF8& utf8, int *outOffset)
{
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen;

	uint32_t utf8CharCount = 0;
	int i = 0;
	bool c1 = false, c2 = false, c3 = false, c4 = false;
	int utf8CharLength = 0;

	uint8_t *utf8Buff = NULL;
	int utf8BuffLen = 0;

	CHECK_OFFSET(start, end, ptr, 4)
	memcpy(&utf8CharCount, ptr,4);
	ptr +=4;

	utf8CharCount = ::BigToHost32(&utf8CharCount);
	i = utf8CharCount;
	while (i > 0)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || (*ptr) == 0xf4;

		if (c1)
			utf8CharLength = 1;
		else if (c2)
			utf8CharLength = 2;
		else if (c3)
			utf8CharLength = 3;
		else if (c4)
			utf8CharLength = 4;
		else
			return INVALID_UTF8_CHAR;

		CHECK_OFFSET(start, end, ptr, utf8CharLength)
		ptr += utf8CharLength;
		i--;
	}

	utf8BuffLen = ptr - start - 4;
	utf8Buff = new uint8_t[utf8BuffLen];
	memcpy(utf8Buff, start + 4, utf8BuffLen);

	*outOffset = ptr - start;
	utf8.buff = utf8Buff;
	utf8.buffLength = utf8BuffLen;
	return SAR_OK;
}


