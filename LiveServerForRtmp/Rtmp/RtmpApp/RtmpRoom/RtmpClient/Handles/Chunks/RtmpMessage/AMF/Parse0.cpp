#include "AMF0.h"
using namespace AMF0;

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off >= end - 1 ) return ERROR_LOSS_DATA;

CParse::CParse()
{

}
CParse::~CParse()
{
	auto it = m_Datas.begin();
	for (it = m_Datas.begin();it != m_Datas.end(); it++)
		Data_free(**(it));
	m_Datas.clear();
}

CParse* CParse::Create(uint8_t *src, const int srcLen)
{
	CParse* parse = new CParse;
	Data *pData = NULL;
	uint8_t *ptr = src;
	const uint8_t *start = src, *end = src + srcLen ;
	int len = 0;
	int ret = AMF0_OK;

	while (ptr != end)
	{
		pData = new Data;
		ret = CParse::ParseData(ptr, end - ptr, *pData, &len);
		if (ret == AMF0_OK)
			parse->m_Datas.push_back(pData);
		ptr += len;
	}

	return parse;
}
void CParse::Destroy()
{
	delete this;
}

int CParse::ParseData(uint8_t *src, const int srcLen, Data& data, int *outLen)
{
	if (src == NULL) return NULL;
	int ret = AMF0_OK;
	uint8_t *ptr = src;
	const uint8_t *start = src, *end = src + srcLen;
	int len = 0;

	CHECK_OFFSET(start, end, ptr, 1)
	data.dType = *ptr;
	memset(&(data.dValue), 0, sizeof(Variable));

	ptr += 1;
	switch (data.dType)
	{
	case MARKER_NUMBER:
		data.dValue.pNum = new Number;
		ret = ParseNumber(ptr, end - ptr, *(data.dValue.pNum), &len);
		break;
	case MARKER_BOOLEAN:
		data.dValue.pBool = new Boolean;
		ret = ParseBoolean(ptr, end - ptr, *(data.dValue.pBool), &len);
		break;
	case MARKER_STRING:
		data.dValue.pStr = new String;
		ret = ParseString(ptr, end - ptr, *(data.dValue.pStr), &len);
		break;
	case MARKER_OBJECT:
		data.dValue.pObj = new Object;
		ret = ParseObject(ptr, end - ptr, *(data.dValue.pObj), &len);
		break;
	case MARKER_MOVIECLIP:
		ret = ParseMovieClip(ptr, end - ptr, &len);
		break;
	case MARKER_NULL:
		ret = ParseNull(ptr, end - ptr, &len);
		break;
	case MARKER_UNDEFINED:
		ret = ParseUndefined(ptr, end - ptr, &len);
		break;
	case MARKER_REFERENCE:
		data.dValue.pRef = new Reference;
		ret = ParseReference(ptr, end - ptr, *(data.dValue.pRef), &len);
		break;
	case MARKER_ECMA_ARRAY:
		data.dValue.pECMA = new ECMA_Array;
		ret = ParseEcmaArray(ptr, end - ptr, *(data.dValue.pECMA), &len);
		break;
	case MARKER_OBJECT_END:
		ret = ParseObjectEnd(ptr, end - ptr, &len);
		break;
	case MARKER_STRICT_ARRAY:
		data.dValue.pStrArr = new StrictArray;
		ret = ParseStrictArray(ptr, end - ptr, *(data.dValue.pStrArr), &len);
		break;
	case MARKER_DATE:
		data.dValue.pDate = new Date;
		ret = ParseDate(ptr, end - ptr, *(data.dValue.pDate), &len);
		break;
	case MARKER_LONG_STRING:
		data.dValue.pLonStr = new LongString;
		ret = ParseLongString(ptr, end - ptr, *(data.dValue.pLonStr), &len);
		break;
	case MARKER_UNSUPPORTED:
		ret = ParseUnsupported(ptr, end - ptr, &len);
		break;
	case MARKER_RECORDSET:
		ret = ParseRecordSet(ptr, end - ptr, &len);
		break;
	case MARKER_XML_DOCUMENT:
		data.dValue.pXML = new XML_Document;
		ret = ParseXmlDocument(ptr, end - ptr, *(data.dValue.pXML), &len);
		break;
	case MARKER_TYPE_OBJECT:
		data.dValue.pTypeObj = new TypedObject;
		ret = ParseTypeObject(ptr, end - ptr, *(data.dValue.pTypeObj), &len);
		break;
	default:
		ret = AMF0_FAILURE;
		break;
	}

	if (ret != AMF0_OK)
		goto parseErr;

	ptr += len;
	*outLen = ptr - start;
	return AMF0_OK;

parseErr:
	*outLen = 0;
	return ret;
}

int CParse::ParseNumber(uint8_t *src, const int srcLen, Number& number, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen;

	CHECK_OFFSET(start, end, ptr, 8);
	number.num = BigToHostDouble(ptr, 8);
	ptr += 8;

	*outLen = ptr - start;
	return AMF0_OK;
}

int CParse::ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;

	CHECK_OFFSET(start, end, ptr, 1);
	boolData.bol = *ptr;
	ptr += 1;

	*outLen = ptr - start;
	return AMF0_OK;
}

int CParse::ParseString(uint8_t *src, const int srcLen, String& str, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen ;
	uint8_t *ptr = src;
	uint16_t utf8CharCount = 0;
	int i = 0;
	bool c1, c2, c3, c4;
	int singleUtf8CharLen = 0;

	CHECK_OFFSET(start, end, ptr, 2)
		utf8CharCount = ::BigToHost16(ptr);
	ptr += 2;
	for (i = 0;i < utf8CharCount;i++)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || (*ptr) == 0xf4;

		if (c1)
			singleUtf8CharLen = 1;
		else if (c2)
			singleUtf8CharLen = 2;
		else if (c3)
			singleUtf8CharLen = 3;
		else if (c4)
			singleUtf8CharLen = 4;
		else
			return ERROR_INVALID_UTF8;

		CHECK_OFFSET(start, end, ptr, singleUtf8CharLen)
			ptr += singleUtf8CharLen;
	}

	str.utf8.len = ptr - 2 - start;
	str.utf8.ptr = new uint8_t[str.utf8.len];
	memcpy(str.utf8.ptr, src + 2, str.utf8.len);

	*outLen = ptr - start;
	return AMF0_OK;
}

int CParse::ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;
	int ret = AMF0_OK;
	int len = 0;

	Member *pMem = NULL;
	vector<Member*> pMems;
	auto it = pMems.begin();

	while (1)
	{
		pMem = new Member;

		ret = ParseObjectProperty(ptr, end - ptr, *pMem, &len);
		if (ret == END_OF_OBJECT)
		{
			Member_free(*pMem);
			ptr += len;
			break;
		}
		else if (ret == NO_END_OF_OBJECT)
		{
			ptr += len;
			pMems.push_back(pMem);
			continue;
		}
		else
			goto parseErr;
	}

	obj.count = pMems.size();
	obj.pMems = new Member[obj.count];
	for (int i = 0;i < obj.count;i++)
		Member_copy(obj.pMems[i], *(pMems.at(i)));

	for (it = pMems.begin();it != pMems.end();it++)
	{
		Member_free(**it);
		(*it) = NULL;
	}

	return AMF0_OK;
parseErr:
	for (it = pMems.begin();it != pMems.end();it++)
	{
		Member_free(**it);
		(*it) = NULL;
	}

	*outLen = 0;
	return ret;
}

int CParse::ParseMovieClip(uint8_t *src, const int srcLen, int* outLen)
{
	return AMF0_FAILURE;
}

int CParse::ParseNull(uint8_t *src, const int srcLen, int* outLen)
{
	*outLen = 0;
	return AMF0_OK;
}

int CParse::ParseUndefined(uint8_t *src, const int srcLen, int* outLen)
{
	*outLen = 0;
	return AMF0_OK;
}

int CParse::ParseReference(uint8_t *src, const int srcLen, Reference &refer, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen;

	CHECK_OFFSET(start, end, ptr, 2)
		refer.ref = ::BigToHost16(ptr);
	ptr += 2;

	*outLen = ptr - start;
	return SAR_OK;
}

int CParse::ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen ;
	int i = 0;
	int ret = AMF0_FAILURE;
	int len = 0;

	CHECK_OFFSET(start, end, ptr, 4)
		ecma.count = ::BigToHost32(ptr);
	ecma.pMems = new Member[ecma.count];

	ptr += 4;
	for (i = 0;i < ecma.count;i++)
	{
		len = 0;
		ret = ParseObjectProperty(ptr, end - ptr, ecma.pMems[i], &len);
		if (ret != AMF0_OK)
			goto PARSE_ERR;
		ptr += len;
	}

	*outLen = ptr - start;
	return SAR_OK;

PARSE_ERR:
	ECMA_Array_free(ecma);
	return ret;
}

int CParse::ParseObjectEnd(uint8_t *src, const int srcLen, int* outLen)
{
	return AMF0_FAILURE;
}

int CParse::ParseStrictArray(uint8_t *src, const int srcLen, StrictArray& strictArray, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen;
	int i;
	int ret;
	int len;

	CHECK_OFFSET(start, end, ptr, 4)
		strictArray.count = ::BigToHost32(ptr);
	strictArray.pDatas = new Data[strictArray.count];

	ptr += 4;
	for (i = 0;i < strictArray.count;i++)
	{
		ret = ParseData((ptr), (end - ptr), (strictArray.pDatas[i]), (&len));
		if (ret != AMF0_OK)
			goto parseErr;
		ptr += len;
	}

	*outLen = ptr - start;

	return AMF0_OK;
parseErr:
	StrictArray_free(strictArray);
	*outLen = 0;
	return ret;
}

int CParse::ParseDate(uint8_t *src, const int srcLen, Date& date, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen;
	int ret = AMF0_FAILURE;

	CHECK_OFFSET(start, end, ptr, 10)	// 8bytes + 2 bytes
		date.date = ::BigToHostDouble(ptr, 8);
	ptr += 10;
	*outLen = ptr - start;
	return SAR_OK;
}

int CParse::ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;
	uint32_t utf8CharCount = 0;
	int i = 0;
	bool c1, c2, c3, c4;
	int singleUtf8CharLen = 0;

	CHECK_OFFSET(start, end, ptr, 4)
		utf8CharCount = ::BigToHost32(ptr);
	ptr += 4;
	for (i = 0;i < utf8CharCount;i++)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || (*ptr) == 0xf4;

		if (c1)
			singleUtf8CharLen = 1;
		else if (c2)
			singleUtf8CharLen = 2;
		else if (c3)
			singleUtf8CharLen = 3;
		else if (c4)
			singleUtf8CharLen = 4;
		else
			return ERROR_INVALID_UTF8;

		CHECK_OFFSET(start, end, ptr, singleUtf8CharLen)
			ptr += singleUtf8CharLen;
	}

	utf8.utf8.len = ptr - 4 - start;
	utf8.utf8.ptr = new uint8_t[utf8.utf8.len];
	memcpy(utf8.utf8.ptr, src + 4, utf8.utf8.len);

	*outLen = ptr - start;
	return AMF0_OK;
}

int CParse::ParseUnsupported(uint8_t *src, const int srcLen, int* outLen)
{
	return AMF0_FAILURE;
}

int CParse::ParseRecordSet(uint8_t *src, const int srcLen, int* outLen)
{
	return AMF0_FAILURE;
}

int CParse::ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &utf8, int* outLen)
{
	int len = 0;
	LongString longUtf8;

	len =  ParseLongString(src, srcLen, longUtf8, outLen);
	Utf8_copy(utf8.utf8,longUtf8.utf8);
	return len;
}

int CParse::ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outLen)
{
	return -1;
}

int CParse::ParseObjectProperty(uint8_t *src, const int srcLen, Member& mem, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen ;
	uint8_t *ptr = src;
	int ret;
	int len = 0;
	String name = {0};

	CHECK_OFFSET(start, end, ptr, 3)
		if (ptr[0] == 0x00 && ptr[1] == 0x00 && ptr[2] == MARKER_OBJECT_END)
		{
			ptr += 3;
			*outLen = ptr - start;
			return END_OF_OBJECT;
		}
		else
		{
			ret = ParseString(ptr, end - ptr, name, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			Utf8_copy(mem.name, name.utf8);
			String_free(name);
			ptr += len;


			ret = ParseData(ptr, end - ptr, mem.value, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;

			*outLen = ptr - start;
			return NO_END_OF_OBJECT;
		}

	return AMF0_OK;
parseErr:
	Utf8_free(mem.name);
	Data_free(mem.value);
	*outLen = 0;
	return ret;
}