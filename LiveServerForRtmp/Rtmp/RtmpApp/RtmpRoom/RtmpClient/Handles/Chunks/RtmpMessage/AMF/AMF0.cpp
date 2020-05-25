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
void AMF0::Undefined_free(Undefined& val){ return NullData_free(val.nData); }

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
		
		break;
	case MARKER_NULL: break;
	case MARKER_UNDEFINED: break;
	case MARKER_REFERENCE: break;
	case MARKER_ECMA_ARRAY: break;
	case MARKER_OBJECT_END: break;
	case MARKER_STRICT_ARRAY: break;
	case MARKER_DATE: break;
	case MARKER_LONG_STRING: break;
	case MARKER_UNSUPPORTED: break;
	case MARKER_RECORDSET: break;
	case MARKER_XML_DOCUMENT: break;
	case MARKER_TYPE_OBJECT: break;
	default:
		break;
	}
}
void AMF0::Data_free(Data& val)
{
	switch (val.dType)
	{
	default:
		break;
	}
}