#include "AMF0.h"
using namespace AMF0;

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off  >= end ) return ERROR_LOSS_DATA;

void Utf8_copy(Utf8& dst,Utf8& src)
{
	if (src.ptr)
	{
		Utf8_free(dst);
		dst.len = src.len;
		dst.ptr = new uint8_t[dst.len];
		memcpy(dst.ptr,src.ptr,dst.len);
	}
	else 
	{ 
		dst.ptr = NULL;
		dst.len = 0;
	}
}
void Utf8_free(Utf8& utf8)
{
	if(utf8.ptr) delete[] utf8.ptr;
	utf8.ptr = NULL;
	utf8.len = 0;
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

void NullData_copy(NullData &dst,NullData &src){}
void NullData_free(NullData& val){}

void AMF0::Number_copy(Number& dst, Number& src){dst.num = src.num;}
void AMF0::Number_free(Number& val){}

void AMF0::Boolean_copy(Boolean& dst, Boolean& src){dst.bol = src.bol;}
void AMF0::Boolean_free(Boolean& val){}

void AMF0::String_copy(String& dst, String& src){return Utf8_copy(dst.utf8,src.utf8);}
void AMF0::String_free(String& val){return Utf8_free(val.utf8);}

void AMF0::Object_copy(Object& dst, Object& src)
{
	int i = 0;
	if (src.count > 0)
	{
		dst.count = src.count;
		dst.pMems = new AMF0::Member[dst.count];
		for (i=0;i<dst.count;i++)
			Member_copy(dst.pMems[i],src.pMems[i]);
	}
	else
	{	
		Object_free(dst);
	}
	
}
void AMF0::Object_free(Object& val)
{
	int i = 0;
	for (i=0;i<val.count;i++)
		Member_free(val.pMems[i]);
	if (val.count > 0)
	{
		val.count = 0;
		delete[] val.pMems;
		val.pMems = NULL;
	}
	
}

void AMF0::Movieclip_copy(Movieclip& dst, Movieclip& src){return NullData_copy(dst.nData,src.nData);}
void AMF0::Movieclip_free(Movieclip& val){return NullData_free(val.nData);}

void AMF0::Null_copy(Null& dst, Null& src){return NullData_copy(dst.nData,src.nData);}
void AMF0::Null_free(Null& val){return NullData_free(val.nData);}

void AMF0::Undefined_copy(Undefined& dst, Undefined& src){ return NullData_copy(dst.nData, src.nData);}
void AMF0::Undefined_free(Undefined& val){ return NullData_free(val.nData);}

void AMF0::Reference_copy(Reference& dst, Reference& src){dst.ref = src.ref;}
void AMF0::Reference_free(Reference& val){val.ref = 0;}

void AMF0::ECMA_Array_copy(ECMA_Array& dst, ECMA_Array& src)
{
	int i = 0;

	if (src.count > 0)
	{
		dst.count = src.count;
		dst.pMems = new AMF0::Member[dst.count];
		for (i=0;i<dst.count;i++)
			Member_copy(dst.pMems[i],src.pMems[i]);
	}
	else
	{
		dst.count = 0;
		dst.pMems = NULL;
	}
}
void AMF0::ECMA_Array_free(ECMA_Array& val)
{	
	int i = 0;
	for (i=0;i<val.count;i++)
		Member_free(val.pMems[i]);
	if (val.count > 0)
	{
		val.count = 0;
		delete[] val.pMems;
		val.pMems = NULL;
	}
}

void AMF0::ObjectEnd_copy(ObjectEnd& dst, ObjectEnd& src){return NullData_copy(dst.nData,src.nData);}
void AMF0::ObjectEnd_free(ObjectEnd& val){return NullData_free(val.nData);}

void AMF0::StrictArray_copy(StrictArray& dst, StrictArray& src)
{
	int i = 0;
	if (src.count > 0)
	{
		dst.count = src.count;
		dst.pDatas = new AMF0::Data[dst.count];
		for (i = 0; i < dst.count; i++)
			Data_copy(dst.pDatas[i], src.pDatas[i]);
	}
	else
	{
		dst.count = 0;
		dst.pDatas = NULL;
	}
	
}
void AMF0::StrictArray_free(StrictArray& val)
{
	int i = 0;
	for (i=0;i<val.count;i++)
		Data_free(val.pDatas[i]);
	if (val.pDatas)
	{
		delete[] val.pDatas;
		val.count = 0;
		val.pDatas = NULL;
	}
}

void AMF0::Date_copy(Date& dst, Date& src){dst.date = src.date;}
void AMF0::Date_free(Date& val){val.date = 0;}

void AMF0::LongString_copy(LongString& dst, LongString& src){return Utf8_copy(dst.utf8,src.utf8); }
void AMF0::LongString_free(LongString& val){return Utf8_free(val.utf8);}

void AMF0::Unsupported_copy(Unsupported& dst, Unsupported& src){ return NullData_copy(dst.nData, src.nData); }
void AMF0::Unsupported_free(Unsupported& val){ return NullData_free(val.nData); }

void AMF0::RecordSet_copy(RecordSet& dst, RecordSet& src){ return NullData_copy(dst.nData, src.nData); }
void AMF0::RecordSet_free(RecordSet& val){ return NullData_free(val.nData); }

void AMF0::XML_Document_copy(XML_Document& dst, XML_Document& src){return Utf8_copy(dst.utf8,src.utf8);}
void AMF0::XML_Document_free(XML_Document& val) {return Utf8_free(val.utf8);}

void AMF0::TypedObject_copy(TypedObject& dst, TypedObject& src)
{
	int i = 0;
	if (src.count > 0)
	{
		Utf8_copy(dst.className, src.className);

		dst.count = src.count;
		dst.pMems = new AMF0::Member[dst.count];
		for (i=0;i<src.count;i++)
			Member_copy(dst.pMems[i],src.pMems[i]);
	}
	else
	{
		Utf8_free(dst.className);
		dst.count = 0;
		dst.pMems = NULL;
	}
	
}
void AMF0::TypedObject_free(TypedObject& val)
{
	int i = 0;
	if (val.count > 0)
	{
		Utf8_free(val.className);
		for ( i = 0; i < val.count; i++)
			Member_free(val.pMems[i]);
		delete[] val.pMems;
		val.pMems = NULL;
	}
}

void AMF0::Member_copy(Member& dst, Member& src)
{
	Utf8_copy(dst.name,src.name);
	Data_copy(dst.value,src.value);
}

void AMF0::Member_free(Member& val)
{
	Utf8_free(val.name);
	Data_free(val.value);
}

void AMF0::Data_copy(Data& dst, Data& src)
{
	Data_free(dst);
	dst.dType = src.dType;
	switch (dst.dType)
	{
	case MARKER_NUMBER:
		dst.dValue.pNum = new Number;
		Number_copy(*(dst.dValue.pNum),*(src.dValue.pNum));
		break;
	case MARKER_BOOLEAN:
		dst.dValue.pBool = new Boolean;
		Boolean_copy(*(dst.dValue.pBool), *(src.dValue.pBool));
		break;
	case MARKER_STRING: 
		dst.dValue.pStr = new String;
		String_copy(*(dst.dValue.pStr),*(src.dValue.pStr));
		break;
	case MARKER_OBJECT: 
		dst.dValue.pObj = new Object;
		Object_copy(*(dst.dValue.pObj),*(src.dValue.pObj));
		break;
	case MARKER_MOVIECLIP: 
		dst.dValue.pMov = new Movieclip;
		Movieclip_copy(*(dst.dValue.pMov),*(src.dValue.pMov));
		break;
	case MARKER_NULL: 
		dst.dValue.pNull = new Null;
		Null_copy(*(dst.dValue.pNull),*(src.dValue.pNull));
		break;
	case MARKER_UNDEFINED: 
		dst.dValue.pUnd = new Undefined;
		Undefined_copy(*(dst.dValue.pUnd),*(src.dValue.pUnd));
		break;
	case MARKER_REFERENCE: 
		dst.dValue.pRef = new Reference;
		Reference_copy(*(dst.dValue.pRef),*(src.dValue.pRef));
		break;
	case MARKER_ECMA_ARRAY:
		dst.dValue.pECMA = new ECMA_Array;
		ECMA_Array_copy(*(dst.dValue.pECMA),*(src.dValue.pECMA));
		break;
	case MARKER_OBJECT_END: 
		dst.dValue.pObjEnd = new ObjectEnd;
		ObjectEnd_copy(*(dst.dValue.pObjEnd),*(src.dValue.pObjEnd));
		break;
	case MARKER_STRICT_ARRAY: 
		dst.dValue.pStrArr = new StrictArray;
		StrictArray_copy(*(dst.dValue.pStrArr),*(src.dValue.pStrArr));
		break;
	case MARKER_DATE: 
		dst.dValue.pDate = new Date;
		Date_copy(*(dst.dValue.pDate),*(src.dValue.pDate));
		break;
	case MARKER_LONG_STRING: 
		dst.dValue.pLonStr = new LongString;
		LongString_copy(*(dst.dValue.pLonStr),*(src.dValue.pLonStr));
		break;
	case MARKER_UNSUPPORTED: 
		dst.dValue.pUns = new Unsupported;
		Unsupported_copy(*(dst.dValue.pUns),*(src.dValue.pUns));
		break;
	case MARKER_RECORDSET: 
		dst.dValue.pRec = new RecordSet;
		RecordSet_copy(*(dst.dValue.pRec),*(src.dValue.pRec));
		break;
	case MARKER_XML_DOCUMENT: 
		dst.dValue.pXML = new XML_Document;
		XML_Document_copy(*(dst.dValue.pXML),*(src.dValue.pXML));
		break;
	case MARKER_TYPE_OBJECT: 
		dst.dValue.pTypeObj = new TypedObject;
		TypedObject_copy(*(dst.dValue.pTypeObj),*(src.dValue.pTypeObj));
		break;
	default:
		break;
	}
}
void AMF0::Data_free(Data& val)
{
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
		String_free(*(val.dValue.pStr));
		delete val.dValue.pStr;
		break;
	case MARKER_OBJECT:
		Object_free(*val.dValue.pObj);
		delete val.dValue.pObj;
		break;
	case MARKER_MOVIECLIP:
		Movieclip_free(*val.dValue.pMov);
		delete val.dValue.pMov;
		break;
	case MARKER_NULL:
		Null_free(*val.dValue.pNull);
		delete val.dValue.pNull;
		break;
	case MARKER_UNDEFINED:
		Undefined_free(*val.dValue.pUnd);
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
		ObjectEnd_free(*val.dValue.pObjEnd);
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
		LongString_free(*val.dValue.pLonStr);
		delete val.dValue.pLonStr;
		break;
	case MARKER_UNSUPPORTED:
		Unsupported_free(*val.dValue.pUns);
		delete val.dValue.pUns;
		break;
	case MARKER_RECORDSET:
		RecordSet_free(*val.dValue.pRec);
		delete val.dValue.pRec;
		break;
	case MARKER_XML_DOCUMENT:
		XML_Document_free(*val.dValue.pXML);
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

bool AMF0::IsString(Data& val)
{
	bool isTrue = false;

	isTrue = val.dType == MARKER_STRING || val.dType == MARKER_LONG_STRING || val.dType == MARKER_XML_DOCUMENT;
	return isTrue;
}

bool AMF0::IsNumber(Data& val)
{
	bool isTrue =false;
	isTrue = val.dType == MARKER_NUMBER;
	return isTrue;
}

bool AMF0::IsBoolean(Data& val)
{
	return val.dType == MARKER_BOOLEAN;
}

void AMF0::CopyString(string& dst, Data& src)
{
	int len = 0;
	uint8_t *ptr = NULL;
	char *buff = NULL;
	switch (src.dType)
	{
	case MARKER_STRING:
		len = src.dValue.pStr->utf8.len;
		ptr = src.dValue.pStr->utf8.ptr;
		break;
	case MARKER_LONG_STRING:
		len = src.dValue.pLonStr->utf8.len;
		ptr = src.dValue.pLonStr->utf8.ptr;
		break;
	case MARKER_XML_DOCUMENT:
		len = src.dValue.pXML->utf8.len;
		ptr = src.dValue.pXML->utf8.ptr;
		break;
	default:
		return;
		break;
	}

	buff = new char[len+1];
	memset(buff,0,len+1);
	memcpy(buff,ptr,len);

	dst = buff;
	delete[] buff;
	buff = NULL;
	return ;
}

void AMF0::CopyNumber(int &dst, Data& src)
{
	if(IsNumber(src) == false)
		return;

	int num = (int)src.dValue.pNum->num;
	dst = num;
	return;
}

void AMF0::CopyBoolean(bool &dst, Data& src)
{
	if (IsBoolean(src) == false)
		return;

	dst = src.dValue.pBool->bol;
	return;
}

int AMF0::Utf8Cmp(const char* dst, Utf8& src)
{
	char* srcStr = NULL;
	int len = 0;
	int ret = 0;

	if (src.len <= 0 || src.ptr == NULL)
		return -1;

	len = src.len + 1;
	srcStr = new char[len];
	memset(srcStr,0,len);

	memcpy(srcStr,src.ptr,src.len);

	ret = strcmp(dst,srcStr);
	delete[] srcStr;
	srcStr = NULL;
	return ret;
}