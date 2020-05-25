#include "AMF0.h"

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off  >= end ) return ERROR_LOSS_DATA;


void  Number_free(Number& val) {}
void  Number_copy(Number& dst, Number& src) { dst.num = src.num; }

void  Boolean_free(Boolean& val) {}
void  Boolean_copy(Boolean& dst, Boolean& src) { dst.bol = src.bol; }

void  Utf8_free(Utf8& val)
{
	if (val.ptr) delete[] val.ptr;
	val.ptr = NULL;
	val.len = 0;
}

void  Utf8_copy(Utf8& dst, Utf8& src)
{
	if (src.ptr)
	{
		dst.len = src.len;
		dst.ptr = new uint8_t[dst.len];
		memcpy(dst.ptr, src.ptr, dst.len);
	}
	else
		return;
}

void  ObjectProperty_free(ObjectProperty& val)
{
	Utf8_free(val.name);
	Data_free(val.value);
}
void  ObjectProperty_copy(ObjectProperty& dst, ObjectProperty& src)
{
	Utf8_copy(dst.name, src.name);
	Data_copy(dst.value, src.value);
}

void  Object_free(Object& val) {
	for (int i = 0;i < val.count;i++)
		ObjectProperty_free(val.pObjPros[i]);
}
void  Object_copy(Object& dst, Object& src)
{
	dst.count = src.count;
	if (dst.count > 0)
	{
		dst.pObjPros = new ObjectProperty[dst.count];
		for (int i = 0;i < dst.count;i++)
			ObjectProperty_copy(dst.pObjPros[i], src.pObjPros[i]);
	}
	else
		dst.pObjPros = NULL;
}

void  NullData_free(Movieclip& val) {}
void  NullData_copy(Movieclip& dst, Movieclip& src) {}


void  Reference_free(Reference& val) {}
void  Reference_copy(Reference& dst, Reference& src) { dst.ref = src.ref; }

void  ECMA_Array_free(ECMA_Array& val)
{
	for (int i = 0;i < val.count;i++)
		ObjectProperty_free(val.pObjPros[i]);
}
void  ECMA_Array_copy(ECMA_Array& dst, ECMA_Array& src)
{
	dst.count = src.count;
	if (dst.count > 0)
	{
		dst.pObjPros = new ObjectProperty[dst.count];
		for (int i = 0;i < dst.count;i++)
			ObjectProperty_copy(dst.pObjPros[i], src.pObjPros[i]);
	}
	else
		dst.pObjPros = NULL;
}



void  StrictArray_free(StrictArray& val)
{
	for (int i = 0;i < val.count;i++)
		Data_free(val.pValues[i]);
}
void  StrictArray_copy(StrictArray& dst, StrictArray& src)
{
	dst.count = src.count;
	if (dst.count > 0)
	{
		dst.pValues = new Data[dst.count];
		for (int i = 0;i < dst.count;i++)
			Data_copy(dst.pValues[i], src.pValues[i]);
	}
	else
		dst.pValues = NULL;
}

void  Date_free(Date& val) {}
void  Date_copy(Date& dst, Date& src) { dst.date = src.date; }


void  TypedObject_free(TypedObject& val)
{
	Utf8_free(val.className);
	for (int i = 0;i < val.count;i++)
		ObjectProperty_free(val.pObjPros[i]);
}
void  TypedObject_copy(TypedObject& dst, TypedObject& src)
{
	Utf8_copy(dst.className, src.className);
	dst.count = src.count;
	if (dst.count > 0)
	{
		dst.pObjPros = new ObjectProperty[dst.count];
		for (int i = 0;i < dst.count;i++)
			ObjectProperty_copy(dst.pObjPros[i], src.pObjPros[i]);
	}
	else
		dst.pObjPros = NULL;
}

void  Data_free(Data& val) {
	switch (val.dType)
	{
	case MARKER_NUMBER:
		Number_free(*val.dValue.pNum);
		delete val.dValue.pNum;
		break;
	case MARKER_BOOLEAN:
		Boolean_free(*val.dValue.pBool);
		delete val.dValue.pBool;
		break;
	case MARKER_STRING:
		Utf8_free(*val.dValue.pStr);
		delete val.dValue.pStr;
		break;
	case MARKER_OBJECT:
		Object_free(*val.dValue.pObj);
		delete val.dValue.pObj;
		break;
	case MARKER_MOVIECLIP:
		NullData_free(*val.dValue.pMov);
		delete val.dValue.pMov;
		break;
	case MARKER_NULL:
		NullData_free(*val.dValue.pNull);
		delete val.dValue.pNull;
		break;
	case MARKER_UNDEFINED:
		NullData_free(*val.dValue.pUnd);
		delete val.dValue.pUnd;
		break;
	case MARKER_REFERENCE:
		Reference_free(*val.dValue.pRef);
		delete val.dValue.pRef;
		break;
	case MARKER_ECMA_ARRAY:
		ECMA_Array_free(*val.dValue.pECMA);
		delete val.dValue.pECMA;
		break;
	case MARKER_OBJECT_END:
		NullData_free(*val.dValue.pObjEnd);
		delete val.dValue.pObjEnd;
		break;
	case MARKER_STRICT_ARRAY:
		StrictArray_free(*val.dValue.pStrArr);
		delete val.dValue.pStrArr;
		break;
	case MARKER_DATE:
		Date_free(*val.dValue.pDate);
		delete val.dValue.pDate;
		break;
	case MARKER_LONG_STRING:
		Utf8_free(*val.dValue.pLonStr);
		delete val.dValue.pLonStr;
		break;
	case MARKER_UNSUPPORTED:
		NullData_free(*val.dValue.pUns);
		delete val.dValue.pUns;
		break;
	case MARKER_RECORDSET:
		NullData_free(*val.dValue.pRec);
		delete val.dValue.pRec;
		break;
	case MARKER_XML_DOCUMENT:
		Utf8_free(*val.dValue.pXML);
		delete val.dValue.pXML;
		break;
	case MARKER_TYPE_OBJECT:
		TypedObject_free(*val.dValue.pTypeObj);
		delete val.dValue.pTypeObj;
		break;
	default:
		break;
	}

	memset(&(val.dValue), 0, sizeof(Variable));
	return;
}

void  Data_copy(Data& dst, Data& src)
{
	dst.dType = src.dType;
	memset(&(dst.dValue), 0, sizeof(Variable));
	switch (dst.dType)
	{
	case MARKER_NUMBER:
		dst.dValue.pNum = new Number;
		Number_copy(*(dst.dValue.pNum), *(src.dValue.pNum));
		break;
	case MARKER_BOOLEAN:
		dst.dValue.pBool = new Boolean;
		Boolean_copy(*(dst.dValue.pBool), *(src.dValue.pBool));
		break;
	case MARKER_STRING:
		dst.dValue.pStr = new String;
		Utf8_copy(*(dst.dValue.pStr), *(src.dValue.pStr));
		break;
	case MARKER_OBJECT:
		dst.dValue.pObj = new Object;
		Object_copy(*(dst.dValue.pObj), *(src.dValue.pObj));
		break;
	case MARKER_MOVIECLIP:
		dst.dValue.pMov = new Movieclip;
		NullData_copy(*(dst.dValue.pMov), *(src.dValue.pMov));
		break;
	case MARKER_NULL:
		dst.dValue.pNull = new AMF0Null;
		NullData_copy(*(dst.dValue.pNull), *(src.dValue.pNull));
		break;
	case MARKER_UNDEFINED:
		dst.dValue.pUnd = new Undefined;
		NullData_copy(*(dst.dValue.pUnd), *(src.dValue.pUnd));
		break;
	case MARKER_REFERENCE:
		dst.dValue.pRef = new Reference;
		Reference_copy(*(dst.dValue.pRef), *(src.dValue.pRef));
		break;
	case MARKER_ECMA_ARRAY:
		dst.dValue.pECMA = new ECMA_Array;
		ECMA_Array_copy(*(dst.dValue.pECMA), *(src.dValue.pECMA));
		break;
	case MARKER_OBJECT_END:
		dst.dValue.pObjEnd = new ObjectEnd;
		NullData_copy(*(dst.dValue.pObjEnd), *(src.dValue.pObjEnd));
		break;
	case MARKER_STRICT_ARRAY:
		dst.dValue.pStrArr = new StrictArray;
		StrictArray_copy(*(dst.dValue.pStrArr), *(src.dValue.pStrArr));
		break;
	case MARKER_DATE:
		dst.dValue.pDate = new Date;
		Date_copy(*(dst.dValue.pDate), *(src.dValue.pDate));
		break;
	case MARKER_LONG_STRING:
		dst.dValue.pLonStr = new LongString;
		Utf8_copy(*(dst.dValue.pLonStr), *(src.dValue.pLonStr));
		break;
	case MARKER_UNSUPPORTED:
		dst.dValue.pUns = new Unsupported;
		NullData_copy(*(dst.dValue.pUns), *(src.dValue.pUns));
		break;
	case MARKER_RECORDSET:
		dst.dValue.pRec = new RecordSet;
		NullData_copy(*(dst.dValue.pRec), *(src.dValue.pRec));
		break;
	case MARKER_XML_DOCUMENT:
		dst.dValue.pXML = new XML_Document;
		Utf8_copy(*(dst.dValue.pXML), *(src.dValue.pXML));
		break;
	case MARKER_TYPE_OBJECT:
		dst.dValue.pTypeObj = new TypedObject;
		TypedObject_copy(*(dst.dValue.pTypeObj), *(src.dValue.pTypeObj));
		break;
	default:
		break;
	}
}


void  UTF8ToString(string &str, Utf8& utf8)
{
	char* buff = new char[utf8.len + 1];

	memset(buff, 0, utf8.len + 1);
	memcpy(buff, utf8.ptr, utf8.len);

	str = buff;
	delete[] buff;
	buff = NULL;
	return;
}

bool  UTF8IsEqual(const char* str, Utf8& utf8)
{
	char* buff = new char[utf8.len + 1];
	bool isTrue = false;

	memset(buff, 0, utf8.len + 1);
	memcpy(buff, utf8.ptr, utf8.len);
	isTrue = strcmp(str, buff) == 0;

	delete[] buff;
	buff = NULL;
	return isTrue;
}

typedef  CParse CParse;
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
	const uint8_t *start = src, *end = src + srcLen - 1;
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
	const uint8_t *start = src, *end = src + srcLen - 1;
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
	const uint8_t* start = src, *end = src + srcLen - 1;

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
	const uint8_t* start = src, *end = src + srcLen - 1;
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

	str.len = ptr - 2 - start;
	str.ptr = new uint8_t[str.len];
	memcpy(str.ptr, src + 2, str.len);

	*outLen = ptr - start;
	return AMF0_OK;
}

int CParse::ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen - 1;
	uint8_t *ptr = src;
	int ret = AMF0_OK;
	int len = 0;

	ObjectProperty *pObjPro = NULL;
	vector<ObjectProperty*> pros;
	auto it = pros.begin();

	while (1)
	{
		pObjPro = new ObjectProperty;

		ret = ParseObjectProperty(ptr, end - ptr, *pObjPro, &len);
		if (ret == END_OF_OBJECT)
		{
			ObjectProperty_free(*pObjPro);
			ptr += len;
			break;
		}
		else if (ret == NO_END_OF_OBJECT)
		{
			ptr += len;
			pros.push_back(pObjPro);
			continue;
		}
		else
			goto parseErr;
	}

	obj.count = pros.size();
	obj.pObjPros = new ObjectProperty[obj.count];
	for (int i = 0;i < obj.count;i++)
		ObjectProperty_copy(obj.pObjPros[i], *(pros.at(i)));

	for (it = pros.begin();it != pros.end();it++)
	{
		ObjectProperty_free(**it);
		(*it) = NULL;
	}

	return AMF0_OK;
parseErr:
	for (it = pros.begin();it != pros.end();it++)
	{
		ObjectProperty_free(**it);
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
	const uint8_t* start = src, *end = src + srcLen - 1;

	CHECK_OFFSET(start, end, ptr, 2)
		refer.ref = ::BigToHost16(ptr);
	ptr += 2;

	*outLen = ptr - start;
	return SAR_OK;
}

int CParse::ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outLen)
{
	uint8_t *ptr = src;
	const uint8_t* start = src, *end = src + srcLen - 1;
	int i = 0;
	int ret = AMF0_FAILURE;
	int len = 0;

	CHECK_OFFSET(start, end, ptr, 4)
		ecma.count = ::BigToHost32(ptr);
	ecma.pObjPros = new ObjectProperty[ecma.count];

	ptr += 4;
	for (i = 0;i < ecma.count;i++)
	{
		len = 0;
		ret = ParseObjectProperty(ptr, end - ptr, ecma.pObjPros[i], &len);
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
	const uint8_t* start = src, *end = src + srcLen - 1;
	int i;
	int ret;
	int len;

	CHECK_OFFSET(start, end, ptr, 4)
		strictArray.count = ::BigToHost32(ptr);
	strictArray.pValues = new Data[strictArray.count];

	ptr += 4;
	for (i = 0;i < strictArray.count;i++)
	{
		ret = ParseData((ptr), (end - ptr), (strictArray.pValues[i]), (&len));
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
	const uint8_t* start = src, *end = src + srcLen - 1;
	int ret = AMF0_FAILURE;

	CHECK_OFFSET(start, end, ptr, 10)	// 8bytes + 2 bytes
		date.date = ::BigToHostDouble(ptr, 8);
	ptr += 10;
	*outLen = ptr - start;
	return SAR_OK;
}

int CParse::ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen - 1;
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

	utf8.len = ptr - 4 - start;
	utf8.ptr = new uint8_t[utf8.len];
	memcpy(utf8.ptr, src + 4, utf8.len);

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
	return ParseLongString(src, srcLen, utf8, outLen);
}

int CParse::ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outLen)
{

}

int CParse::ParseObjectProperty(uint8_t *src, const int srcLen, ObjectProperty& objPro, int* outLen)
{
	const uint8_t* start = src, *end = src + srcLen - 1;
	uint8_t *ptr = src;
	int ret;
	int len = 0;

	CHECK_OFFSET(start, end, ptr, 3)
		if (ptr[0] == 0x00 && ptr[1] == 0x00 && ptr[2] == MARKER_OBJECT_END)
		{
			ptr += 3;
			*outLen = ptr - start;
			return END_OF_OBJECT;
		}
		else
		{
			ret = ParseString(ptr, end - ptr, objPro.name, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;

			ret = ParseData(ptr, end - ptr, objPro.value, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;

			*outLen = ptr - start;
			return NO_END_OF_OBJECT;
		}

	return AMF0_OK;
parseErr:
	Utf8_free(objPro.name);
	Data_free(objPro.value);
	*outLen = 0;
	return ret;
}