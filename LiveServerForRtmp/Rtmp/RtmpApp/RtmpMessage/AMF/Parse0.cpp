#include "AMF0.h"
using namespace AMF0;

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off > end  ) return AMF0_FAILURE;

CParse::CParse()
{

}

CParse::~CParse()
{
	
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
	data.marker = *ptr;

	ptr += 1;
	switch (data.marker)
	{
	case MARKER_NUMBER:
		ret = ParseNumber(ptr, end - ptr, data, &len);
		break;
	case MARKER_BOOLEAN:
		ret = ParseBoolean(ptr, end - ptr, data, &len);
		break;
	case MARKER_STRING:
		ret = ParseString(ptr, end - ptr, data, &len);
		break;
	case MARKER_OBJECT:
		ret = ParseObject(ptr, end - ptr, data, &len);
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
		ret = ParseReference(ptr, end - ptr, data, &len);
		break;
	case MARKER_ECMA_ARRAY:
		ret = ParseEcmaArray(ptr, end - ptr,data, &len);
		break;
	case MARKER_OBJECT_END:
		ret = ParseObjectEnd(ptr, end - ptr, &len);
		break;
	case MARKER_STRICT_ARRAY:
		ret = ParseStrictArray(ptr, end - ptr,data, &len);
		break;
	case MARKER_DATE:
		ret = ParseDate(ptr, end - ptr, data, &len);
		break;
	case MARKER_LONG_STRING:
		ret = ParseLongString(ptr, end - ptr, data, &len);
		break;
	case MARKER_UNSUPPORTED:
		ret = ParseUnsupported(ptr, end - ptr, &len);
		break;
	case MARKER_RECORDSET:
		ret = ParseRecordSet(ptr, end - ptr, &len);
		break;
	case MARKER_XML_DOCUMENT:
		ret = ParseXmlDocument(ptr, end - ptr,data, &len);
		break;
	case MARKER_TYPE_OBJECT:
		ret = ParseTypeObject(ptr, end - ptr, data, &len);
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
	
	AllocDataBuff(number,ptr,8);
	*outLen = 8;
	return AMF0_OK;
}

int CParse::ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;

	CHECK_OFFSET(start, end, ptr, 1);

	
	AllocDataBuff(boolData, ptr, 1);
	*outLen = 1;
	return AMF0_OK;
}

int CParse::ParseString(uint8_t *src, const int srcLen, String& str, int* outLen)
{
	UTF8 utf8;
	int length = 0;

	ParseUTF8(src,srcLen,utf8,&length);
	str.buf = utf8.buf;
	str.len = utf8.len;
	*outLen = length;
	return AMF0_OK;
}

int CParse::ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;
	int ret = AMF0_OK;
	uint8_t tag[3] = {0};

	vector<UTF8*> utf8s;
	vector<Data*> datas;
	UTF8 *utf8 = NULL;
	Data *data = NULL;
	int length = 0;

	while (1)
	{
		CHECK_OFFSET(start,end,ptr,3)
		memcpy(tag,ptr,3);

		if (tag[0] == 0x00 && tag[1] == 0x00 && tag[2] == MARKER_OBJECT_END)
		{
			ptr += 3;
			break;
		}

		utf8 = new UTF8;
		ret = ParseUTF8(ptr,end-ptr,*utf8,&length);
		utf8s.push_back(utf8);
		ptr += length;

		data = new Data;
		ret = ParseData(ptr,end-ptr,*data,&length);
		datas.push_back(data);
		ptr += length;
	}

	obj.len = ptr - start;
	obj.buf = new uint8_t[obj.len];
	memcpy(obj.buf,start,obj.len);
	*outLen = ptr - start;
	return AMF0_OK;
parseErr:
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
	AllocDataBuff(refer,ptr,2);


	*outLen = 2;
	return AMF0_OK;
}

int CParse::ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outLen)
{
	return -1;
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
	int count;
	int length = 0;
	
	vector<Data*> datas;
	Data *data;

	CHECK_OFFSET(start, end, ptr, 4)
	count = ::BigToHost32(ptr);
	ptr += 4;

	for (i=0;i<count;i++)
	{
		data = new Data;
		ret = ParseData(ptr,end-ptr,*data,&length);
		datas.push_back(data);
		ptr += length;
	}

	strictArray.len = ptr - start;
	strictArray.buf = new uint8_t[strictArray.len];
	memcpy(strictArray.buf,start,strictArray.len);

	return AMF0_OK;
}

int CParse::ParseDate(uint8_t *src, const int srcLen, Date& date, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen;
	int ret = AMF0_FAILURE;

	CHECK_OFFSET(start, end, ptr, 10)	// 8bytes + 2 bytes
	AllocDataBuff(date,ptr,10);
	*outLen =10;
	return AMF0_OK;
}

int CParse::ParseLongString(uint8_t *src, const int srcLen, LongString &longStr, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen;
	uint8_t *ptr = src;
	UTF8 utf8;
	int length = 0;

	ParseUTF8Long(src,srcLen,utf8,&length);

	*outLen = length;
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

int CParse::ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &xml, int* outLen)
{
	int length = 0;
	UTF8 utf8;

	ParseUTF8(src,srcLen,utf8,&length);
	xml.buf = utf8.buf;
	xml.len = utf8.len;

	*outLen = length;
	return AMF0_OK;
}

int CParse::ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outLen)
{
	return -1;
}

int CParse::MatchField(Data& src,UTF8 key, Data& value)
{
	const uint8_t *start = src.buf , *end = src.buf + src.len;
	uint8_t *ptr = src.buf;
	UTF8 *pTempUtf8 = NULL;
	Data *pTempData = NULL;
	int length = 0;
	
	while (ptr < end)
	{
		pTempUtf8 = new UTF8;
		ParseUTF8(ptr, end - ptr, *pTempUtf8, &length);
		ptr += length;

		pTempData = new Data;
		ParseData(ptr,end-ptr,*pTempData,&length);
		ptr += length;
		
		if (CompareUtf8(key, *pTempUtf8))
		{
			CopyData(value,*pTempData);
			Utf8Free(&pTempUtf8);
			DataFree(&pTempData);
			return 0;
		}

		Utf8Free(&pTempUtf8);
		DataFree(&pTempData);
	}


	value.marker = MARKER_NONE;
	value.buf = NULL;
	value.len = 0;
	return 0;
}

