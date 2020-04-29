#include "AMF0.h"

namespace AMF0
{
	void NullData_free(NullData& val){}
	void Utf8String_free(Utf8String& val) 
	{
		if (val.ptr) delete[] val.ptr;
		val.ptr = NULL;
		val.len = 0;
	}
	void Number_free(Number& val){}
	void Boolean_free(Boolean& val) {}
	void String_free(String& val) {
		Utf8String_free(val.utf8);
	}
	void ObjectProperty_free(ObjectProperty& val) 
	{
		Utf8String_free(val.name);
		Data_free(val.value);
	}
	void Object_free(Object& val) {
		for (int i=0;i<val.objProCount;i++)
			ObjectProperty_free(val.pObjPros[i]);
	}
	void Movieclip_free(Movieclip& val) {return NullData_free(val);}
	void AMF0Null_free(AMF0Null& val) { return NullData_free(val); }
	void Undefined_free(Undefined& val) { return NullData_free(val); }
	void Reference_free(Reference& val) {}
	void ECMA_Array_free(ECMA_Array& val) 
	{
		for (int i= 0;i<val.count;i++)
			ObjectProperty_free(val.pObjPros[i]);
	}
	void ObjectEnd_free(ObjectEnd& val) {return  NullData_free(val);}
	void StrictArray_free(StrictArray& val) 
	{
		for (int i=0;i<val.count;i++)
			Data_free(val.pValues[i]);
	}
	void Date_free(Date& val) {}
	void LongString_free(LongString& val) {return Utf8String_free(val.utf8Long);}
	void Unsupported_free(Unsupported& val) { return NullData_free(val); }
	void RecordSet_free(RecordSet& val) { return NullData_free(val); }
	void XML_Document_free(XML_Document& val) {return LongString_free(val);}
	void TypedObject_free(TypedObject& val) 
	{
		Utf8String_free(val.className);
		for (int i=0;i<val.count;i++)
			ObjectProperty_free(val.pObjPros[i]);
	}
	void Data_free(Data& val) {
		switch (val.dType)
		{
		case AMF0::NONE:	
			break;
		case AMF0::NUMBER:
			Number_free(*val.dValue.pNum);
			delete val.dValue.pNum;
			break;
		case AMF0::BOOLEAN:
			Boolean_free(*val.dValue.pBool);
			delete val.dValue.pBool;
			break;
		case AMF0::STRING:
			String_free(*val.dValue.pStr);
			delete val.dValue.pStr;
			break;
		case AMF0::OBJECT:
			Object_free(*val.dValue.pObj);
			delete val.dValue.pObj;
			break;
		case AMF0::MOVIECLIP:
			Movieclip_free(*val.dValue.pMov);
			delete val.dValue.pMov;
			break;
		case AMF0::NULL_MARKER:
			AMF0Null_free(*val.dValue.pNull);
			delete val.dValue.pNull;
			break;
		case AMF0::UNDEFINED:
			Undefined_free(*val.dValue.pUnd);
			delete val.dValue.pUnd;
			break;
		case AMF0::REFERENCE:
			Reference_free(*val.dValue.pRef);
			delete val.dValue.pRef;
			break;
		case AMF0::ECMA_ARRAY:
			ECMA_Array_free(*val.dValue.pECMA);
			delete val.dValue.pECMA;
			break;
		case AMF0::OBJECT_END:
			ObjectEnd_free(*val.dValue.pObjEnd);
			delete val.dValue.pObjEnd;
			break;
		case AMF0::STRICT_ARRAY:
			StrictArray_free(*val.dValue.pStrArr);
			delete val.dValue.pStrArr;
			break;
		case AMF0::DATE:
			Date_free(*val.dValue.pDate);
			delete val.dValue.pDate;
			break;
		case AMF0::LONG_STRING:
			LongString_free(*val.dValue.pLonStr);
			delete val.dValue.pLonStr;
			break;
		case AMF0::UNSUPPORTED:
			Unsupported_free(*val.dValue.pUns);
			delete val.dValue.pUns;
			break;
		case AMF0::RECORDSET:
			RecordSet_free(*val.dValue.pRec);
			delete val.dValue.pRec;
			break;
		case AMF0::XML_DOCUMENT:
			XML_Document_free(*val.dValue.pXML);
			delete val.dValue.pXML;
			break;
		case AMF0::TYPE_OBJECT:
			TypedObject_free(*val.dValue.pTypeObj);
			delete val.dValue.pTypeObj;
			break;
		default:	
			break;
		}

		memset(&(val.dValue),0,sizeof(Variable));
		return;
	}

	//
#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off > end ) return ERROR_LOSS_DATA;
	

	CParse::CParse()
	{
	
	}
	CParse::~CParse()
	{
		auto it = m_Datas.begin();
		for (it=m_Datas.begin();it!= m_Datas.end(); it++)
			Data_free(**(it));
		m_Datas.clear();
	}

	CParse* CParse::Create(uint8_t *src, const int srcLen)
	{
		CParse* parse = new CParse;
		Data *pData = NULL;
		int offset = 0;
		return parse;
	}
	void CParse::Destroy()
	{
		delete this;
	}


	int CParse::ParseData(uint8_t *src, const int srcLen, Data& data, int *outOffset)
	{
		if (src == NULL) return NULL;
		int ret = AMF0_OK;
		uint8_t *ptr = src;
		const uint8_t *start = src ,*end = src+srcLen-1;
		int len = 0;

		CHECK_OFFSET(start,end,ptr,1)
		data.dType = (DataType)*ptr;
		memset(&(data.dValue),0,sizeof(Variable));

		ptr += 1;
		switch (data.dType)
		{
		case DataType::NONE:	ret = AMF0_FAILURE;	break;
		case DataType::NUMBER:
			data.dValue.pNum = new Number;
			ret = ParseNumber(ptr,end-ptr, *(data.dValue.pNum),&len);
			break;
		case DataType::BOOLEAN:
			data.dValue.pBool = new Boolean;
			ret = ParseBoolean(ptr,end-ptr,*(data.dValue.pBool),&len);
			break;
		case DataType::STRING:
			data.dValue.pStr = new String;
			ret = ParseString(ptr,end-ptr,*(data.dValue.pStr),&len);
			break;
		case DataType::OBJECT:
			data.dValue.pObj = new Object;
			ret = ParseObject(ptr,end-ptr,*(data.dValue.pObj),&len);
			break;
		case DataType::MOVIECLIP:
			ret = ParseMovieClip(ptr,end-ptr,&len);
			break;
		case DataType::NULL_MARKER:
			ret = ParseNull(ptr,end-ptr,&len);
			break;
		case DataType::UNDEFINED:
			ret = ParseUndefined(ptr,end-ptr,&len);
			break;
		case DataType::REFERENCE:
			data.dValue.pRef = new Reference;
			ret = ParseReference(ptr,end-ptr,*(data.dValue.pRef),&len);
			break;
		case DataType::ECMA_ARRAY:
			data.dValue.pECMA = new ECMA_Array;
			ret = ParseEcmaArray(ptr,end-ptr,*(data.dValue.pECMA),&len);
			break;
		case DataType::OBJECT_END:
			ret = ParseObjectEnd(ptr,end-ptr,&len);
			break;
		case DataType::STRICT_ARRAY:
			data.dValue.pStrArr = new StrictArray;
			ret = ParseStrictArray(ptr,end-ptr,*(data.dValue.pStrArr),&len);
			break;
		case DataType::DATE:
			data.dValue.pDate = new Date;
			ret = ParseDate(ptr,end-ptr,*(data.dValue.pDate),&len);
			break;
		case DataType::LONG_STRING:
			data.dValue.pLonStr = new LongString;
			ret = ParseLongString(ptr,end-ptr,*(data.dValue.pLonStr),&len);
			break;
		case DataType::UNSUPPORTED:
			ret = ParseUnsupported(ptr,end-ptr,&len);
			break;
		case DataType::RECORDSET:
			ret = ParseRecordSet(ptr,end-ptr,&len);
			break;
		case DataType::XML_DOCUMENT:
			data.dValue.pXML = new XML_Document;
			ret = ParseXmlDocument(ptr,end-ptr,*(data.dValue.pXML),&len);
			break;
		case DataType::TYPE_OBJECT:
			data.dValue.pTypeObj = new TypedObject;
			ret = ParseTypeObject(ptr,end-ptr,*(data.dValue.pTypeObj),&len);
			break;
		default:	ret = AMF0_FAILURE;	break;
		}

		if (ret != AMF0_OK)
			goto parseErr;
		
		ptr += len;
		*outOffset = end - ptr;
		return AMF0_OK;
		
parseErr:
	*outOffset = 0;
	return ret;	
	}

	int CParse::ParseNumber(uint8_t *src, const int srcLen, Number& number, int* outOffset)
	{
		const uint8_t* start = src, *end = src + srcLen - 1;
		uint8_t *ptr = src;

		CHECK_OFFSET(start, end, ptr, 8);
		number.num = BigToHostDouble(src, 8);
		ptr += 8;

		*outOffset = ptr-start;
		return AMF0_OK;
	}

	int CParse::ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outOffset)
	{
		const uint8_t* start = src, *end = src + srcLen - 1;
		uint8_t *ptr = src;
		
		CHECK_OFFSET(start, end, ptr, 1);
		boolData.bol = *ptr;
		ptr += 1;

		*outOffset = ptr-start;
		return AMF0_OK;
	}

	

	int CParse::ParseString(uint8_t *src, const int srcLen, String& str, int* outOffset)
	{
		return ParseUtf8(src,srcLen,str.utf8,outOffset);
	}

	int CParse::ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outOffset)
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

			ret = ParseObjectProperty(ptr,end-ptr,*pObjPro,&len);
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

		obj.objProCount = pros.size();
		obj.pObjPros = new ObjectProperty[obj.objProCount];

		

		return AMF0_OK;
	parseErr:
		for (it = pros.begin();it != pros.end();it++)
		{
			ObjectProperty_free(**it);
			(*it) = NULL;
		}

		*outOffset = 0;
		return ret;
	}

	int CParse::ParseMovieClip(uint8_t *src, const int srcLen, int* outOffset)
	{
		return AMF0_FAILURE;
	}

	int CParse::ParseNull(uint8_t *src, const int srcLen, int* outOffset)
	{
		*outOffset = 0;
		return AMF0_OK;
	}

	int CParse::ParseUndefined(uint8_t *src, const int srcLen, int* outOffset)
	{
		*outOffset = 0;
		return AMF0_OK;
	}

	int CParse::ParseReference(uint8_t *src, const int srcLen, Reference &refer, int* outOffset)
	{
		uint8_t *ptr = src;
		const uint8_t* start = src, *end = src + srcLen - 1;

		CHECK_OFFSET(start, end, ptr, 2)
		refer.ref = ::BigToHost16(ptr);
		ptr += 2;

		*outOffset = ptr - start;
		return SAR_OK;
	}

	int CParse::ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outOffset)
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
		for (i=0;i<ecma.count;i++)
		{
			len = 0;
			ret = ParseObjectProperty(ptr,end-ptr,ecma.pObjPros[i],&len);
			if (ret != AMF0_OK)
				goto PARSE_ERR;
			ptr += len;
		}

		*outOffset = ptr - start;
		return SAR_OK;

	PARSE_ERR:
		ECMA_Array_free(ecma);
		return ret;
	}

	int CParse::ParseObjectEnd(uint8_t *src, const int srcLen, int* outOffset)
	{
		return AMF0_FAILURE;
	}

	int CParse::ParseStrictArray(uint8_t *src, const int srcLen, StrictArray& strictArray, int* outOffset)
	{
		uint8_t *ptr = src;
		const uint8_t* start = src, *end = src + srcLen - 1;
		int i;
		int ret ;
		int len;

		CHECK_OFFSET(start,end,ptr,4)
		strictArray.count = ::BigToHost32(ptr);
		strictArray.pValues = new Data[strictArray.count];

		ptr += 4;
		for (i=0;i<strictArray.count;i++)
		{
			ret = ParseData(ptr,end-ptr,strictArray.pValues[i],&len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;
		}

		*outOffset = ptr - start;

		return AMF0_OK;
		parseErr:
			StrictArray_free(strictArray);
			*outOffset = 0;
			return ret;
	}

	int CParse::ParseDate(uint8_t *src, const int srcLen, Date& date, int* outOffset)
	{
		uint8_t *ptr = src;
		const uint8_t* start = src, *end = src + srcLen - 1;
		int ret = AMF0_FAILURE;

		CHECK_OFFSET(start, end, ptr, 10)	// 8bytes + 2 bytes
		date.date = ::BigToHostDouble(ptr,8);
		ptr += 10;
		*outOffset = ptr - start;
		return SAR_OK;
	}

	int CParse::ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outOffset)
	{
		return ParseUtf8Long(src,srcLen,utf8.utf8Long,outOffset);
	}

	int CParse::ParseUnsupported(uint8_t *src, const int srcLen, int* outOffset)
	{
		return AMF0_FAILURE;
	}

	int CParse::ParseRecordSet(uint8_t *src, const int srcLen, int* outOffset)
	{
		return AMF0_FAILURE;
	}

	int CParse::ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &utf8, int* outOffset)
	{
		return ParseLongString(src,srcLen, utf8,outOffset);
	}

	int CParse::ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outOffset)
	{

	}

	int CParse::ParseUtf8(uint8_t *src, const int srcLen, Utf8String &utf8, int* outOffset)
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

		utf8.len = ptr - 2 - start;
		utf8.ptr = new uint8_t[utf8.len];
		memcpy(utf8.ptr, src + 2, utf8.len);

		*outOffset = ptr - start;
		return AMF0_OK;
	}

	int CParse::ParseUtf8Long(uint8_t *src, const int srcLen, Utf8String &utf8Long, int* outOffset)
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

		utf8Long.len = ptr - 4 - start;
		utf8Long.ptr = new uint8_t[utf8Long.len];
		memcpy(utf8Long.ptr, src + 4, utf8Long.len);

		*outOffset = ptr - start;
		return AMF0_OK;
	}

	int CParse::ParseObjectProperty(uint8_t *src, const int srcLen, ObjectProperty& objPro, int* outOffset)
	{
		const uint8_t* start = src, *end = src + srcLen - 1;
		uint8_t *ptr = src;
		int ret ;
		int len = 0;

		CHECK_OFFSET(start,end,ptr,3)
		if (ptr[0] == 0x00 && ptr[1] == 0x00 && ptr[2] == DataType::OBJECT_END)
		{
			ptr += 3;
			*outOffset = ptr -start;
			return END_OF_OBJECT;
		}
		else
		{
			ret = ParseUtf8(ptr, end - ptr, objPro.name, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;

			ret = ParseData(ptr, end - ptr, objPro.value, &len);
			if (ret != AMF0_OK)
				goto parseErr;
			ptr += len;

			*outOffset = ptr - start;
			return NO_END_OF_OBJECT;
		}

		return AMF0_OK;
	parseErr:
		Utf8String_free(objPro.name);
		Data_free(objPro.value);
		*outOffset = 0;
		return ret;
	}
};

