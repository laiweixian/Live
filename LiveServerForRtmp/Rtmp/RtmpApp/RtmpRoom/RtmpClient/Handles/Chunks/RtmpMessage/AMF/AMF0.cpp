#include "AMF0.h"

namespace AMF0
{
	void Utf8_free(Utf8 &val)
	{
		if (val.ptr != NULL)	delete[](val.ptr);
		val.ptr = NULL;
		val.len = 0;
	}
	void Utf8_init(Utf8 &val)
	{
		val.ptr = NULL;
		val.len = 0;
	}

	void NullData_free(NullData &val){}
	void NullData_init(NullData &val){}

	void Number_free(Number &val){}
	void Number_init(Number &val){val.value = 0;}

	void Boolean_free(Boolean &val){}
	void Boolean_init(Boolean &val){val.value = false;}

	void String_free(String &val){Utf8_free(val.value);}
	void String_init(String &val){Utf8_init(val.value);}

	void Object_free(Object &val)
	{
		int i =0;
		for (i=0;i<val.objProCount;i++)
			ObjectProperty_free(val.pObjPros[i]);
		val.pObjPros = NULL;
		val.objProCount = 0;
	}
	void Object_init(Object &val)
	{
		val.pObjPros = NULL;
		val.objProCount = 0;
	}

	void Movieclip_free(Movieclip &val){return NullData_free(val);}
	void Movieclip_init(Movieclip &val){return NullData_init(val);}

	void AMF0Null_free(AMF0Null &val){return NullData_free(val);}
	void AMF0Null_init(AMF0Null &val){return NullData_init(val);}

	void Undefined_free(Undefined &val){return NullData_free(val);}
	void Undefined_init(Undefined &val){return NullData_init(val);}

	void Reference_free(Reference &val){}
	void Reference_init(Reference &val){val.value = 0;}

	void ECMA_Array_free(ECMA_Array &val)
	{
		int i = 0;
		for (i=0;i<val.count;i++)
			ObjectProperty_free(val.pObjPros[i]);
		val.pObjPros = NULL;
		val.count = 0;
	}
	void ECMA_Array_init(ECMA_Array &val)
	{
		val.count = 0;
		val.pObjPros = NULL;
	}

	void ObjectEnd_free(ObjectEnd &val){return NullData_free(val);}
	void ObjectEnd_init(ObjectEnd &val){return NullData_init(val);}

	void StrictArray_free(StrictArray &val)
	{
		int i = 0;
		for (i=0;i<val.count;i++)
			Data_free(val.pValues[i]);
		val.pValues = NULL;
		val.count = 0;
	}
	void StrictArray_init(StrictArray &val)
	{
		val.count = 0;
		val.pValues = NULL;
	}

	void Date_free(Date &val){}
	void Date_init(Date &val){val.value = 0;}

	void LongString_free(LongString &val){return String_free(val);}
	void LongString_init(LongString &val){return String_init(val);}

	void Unsupported_free(Unsupported &val){return NullData_free(val);}
	void Unsupported_init(Unsupported &val){return NullData_init(val); }

	void RecordSet_free(RecordSet &val){return NullData_free(val);}
	void RecordSet_init(RecordSet &val){return NullData_init(val); }

	void XML_Document_free(XML_Document &val){return LongString_free(val);}
	void XML_Document_init(XML_Document &val){return LongString_init(val);}
	
	void TypedObject_free(TypedObject &val)
	{
		int i = 0;
		Utf8_free(val.className);
		for(i=0;i<val.count;i++)
			ObjectProperty_free(val.pObjPros[i]);
		val.pObjPros = NULL;
		val.count = 0;
	}
	void TypedObject_init(TypedObject &val)
	{
		Utf8_init(val.className);
		val.count = 0;
		val.pObjPros = 0;
	}

	void ObjectProperty_free(ObjectProperty &val)
	{
		Utf8_free(val.name);
		Data_free(val.value);
	}
	void ObjectProperty_init(ObjectProperty &val, DataType dtype)
	{
		Utf8_init(val.name);
		Data_init(val.value, dtype);
	}

	void Data_init(Data& data, DataType dtype)
	{
		Variable var;
		memset(&var,0,sizeof(Variable));
		switch (dtype)
		{
		case AMF0::NONE:
			break;
		case AMF0::NUMBER:
			var.pNum = new Number;
			Number_init(*(var.pNum));
			break;
		case AMF0::BOOLEAN:
			var.pBool = new Boolean;
			Boolean_init(*(var.pBool));
			break;
		case AMF0::STRING:
			var.pStr = new String;
			String_init(*(var.pStr));
			break;
		case AMF0::OBJECT:
			var.pObj = new Object;
			Object_init(*(var.pObj));
			break;
		case AMF0::MOVIECLIP:
			break;
		case AMF0::NULL_MARKER:
			break;
		case AMF0::UNDEFINED:
			break;
		case AMF0::REFERENCE:
			var.pRef = new Reference;
			Reference_init(*(var.pRef));
			break;
		case AMF0::ECMA_ARRAY:
			var.pECMA = new ECMA_Array;
			ECMA_Array_init(*(var.pECMA));
			break;
		case AMF0::OBJECT_END:
			break;
		case AMF0::STRICT_ARRAY:
			var.pStrArr = new StrictArray;
			StrictArray_init(*(var.pStrArr));
			break;
		case AMF0::DATE:
			var.pDate = new Date;
			Date_init(*(var.pDate));
			break;
		case AMF0::LONG_STRING:
			var.pLonStr = new LongString;
			LongString_init(*(var.pLonStr));
			break;
		case AMF0::UNSUPPORTED:
			break;
		case AMF0::RECORDSET:
			break;
		case AMF0::XML_DOCUMENT:
			var.pXML = new XML_Document;
			XML_Document_init(*(var.pXML));
			break;
		case AMF0::TYPE_OBJECT:
			var.pTypeObj = new TypedObject;
			TypedObject_init(*(var.pTypeObj));
			break;
		default:
			break;
		}

		data.dType = dtype;
		data.dValue = var;
	}

	void Data_free(Data& data)
	{
		// free data value
		switch (data.dType)
		{
		case AMF0::NONE:
			data.dValue.pNullData = NULL;
			break;
		case AMF0::NUMBER:
			Number_free(*(data.dValue.pNum));
			break;
		case AMF0::BOOLEAN:
			Boolean_free(*(data.dValue.pBool));
			break;
		case AMF0::STRING:
			String_free(*(data.dValue.pStr));
			break;
		case AMF0::OBJECT:
			Object_free(*(data.dValue.pObj));
			break;
		case AMF0::MOVIECLIP:
			break;
		case AMF0::NULL_MARKER:
			break;
		case AMF0::UNDEFINED:
			break;
		case AMF0::REFERENCE:
			Reference_free(*(data.dValue.pRef));
			break;
		case AMF0::ECMA_ARRAY:
			ECMA_Array_free(*(data.dValue.pECMA));
			break;
		case AMF0::OBJECT_END:
			break;
		case AMF0::STRICT_ARRAY:
			StrictArray_free(*(data.dValue.pStrArr));
			break;
		case AMF0::DATE:
			Date_free(*(data.dValue.pDate));
			break;
		case AMF0::LONG_STRING:
			LongString_free(*(data.dValue.pLonStr));
			break;
		case AMF0::UNSUPPORTED:
			break;
		case AMF0::RECORDSET:
			break;
		case AMF0::XML_DOCUMENT:
			XML_Document_free(*(data.dValue.pXML));
			break;
		case AMF0::TYPE_OBJECT:
			TypedObject_free(*(data.dValue.pTypeObj));
			break;
		default:
			break;
		}
	}

	//
#define CHECK_OFFSET(start,end,ptr,off)	\
	if (ptr + off > end )	return ERROR_LOSS_DATA;
	CParse::CParse(){
	
	}
	CParse::~CParse()
	{
		auto it = m_Datas.begin();
		for (it=m_Datas.begin();it!= m_Datas.end(); it++)
			Data_free(**(it));
		m_Datas.clear();
	}

	Data* CParse::ParseData(uint8_t *src, const int srcLen, int *outOffset)
	{
		if (src == NULL) return NULL;

		Data *p = NULL;;
		int ret = AMF0_OK;
		uint8_t *ptr = src;
		const uint8_t *end = src + srcLen - 1;
		const DataType dType = (DataType) *ptr;
		int len = 0;

		p = new Data;
		Data_init(*p,dType);
		ptr += 1;
		switch (dType)
		{
		case AMF0::NONE:	ret = AMF0_FAILURE;	break;
		case AMF0::NUMBER:
			ret = ParseNumber(ptr,end-ptr, *(p->dValue.pNum),&len);
			break;
		case AMF0::BOOLEAN:
			ret = ParseBoolean(ptr,end-ptr,*(p->dValue.pBool),&len);
			break;
		case AMF0::STRING:
			ret = ParseString(ptr,end-ptr,*(p->dValue.pStr),&len);
			break;
		case AMF0::OBJECT:
			ret = ParseObject(ptr,end-ptr,*(p->dValue.pObj),&len);
			break;
		case AMF0::MOVIECLIP:
			ret = ParseMovieClip(ptr,end-ptr,&len);
			break;
		case AMF0::NULL_MARKER:
			ret = ParseNull(ptr,end-ptr,&len);
			break;
		case AMF0::UNDEFINED:
			ret = ParseUndefined(ptr,end-ptr,&len);
			break;
		case AMF0::REFERENCE:
			ret = ParseReference(ptr,end-ptr,*(p->dValue.pRef),&len);
			break;
		case AMF0::ECMA_ARRAY:
			ret = ParseEcmaArray(ptr,end-ptr,*(p->dValue.pECMA),&len);
			break;
		case AMF0::OBJECT_END:
			ret = ParseObjectEnd(ptr,end-ptr,&len);
			break;
		case AMF0::STRICT_ARRAY:
			ret = ParseStrictArray(ptr,end-ptr,*(p->dValue.pStrArr),&len);
			break;
		case AMF0::DATE:
			ret = ParseDate(ptr,end-ptr,*(p->dValue.pDate),&len);
			break;
		case AMF0::LONG_STRING:
			ret = ParseLongString(ptr,end-ptr,*(p->dValue.pLonStr),&len);
			break;
		case AMF0::UNSUPPORTED:
			ret = ParseUnsupported(ptr,end-ptr,&len);
			break;
		case AMF0::RECORDSET:
			ret = ParseRecordSet(ptr,end-ptr,&len);
			break;
		case AMF0::XML_DOCUMENT:
			
			break;
		case AMF0::TYPE_OBJECT:
	
			break;
		default:
			break;

		}
		
		
parseErr:
	*outOffset = 0;
	return NULL;	


	}

	int CParse::ParseNumber(uint8_t *src, const int srcLen, Number& number, int* outOffset)
	{

	}

	int CParse::ParseBoolean(uint8_t *src, const int srcLen, Boolean& boolData, int* outOffset)
	{

	}

	int CParse::ParseString(uint8_t *src, const int srcLen, String& utf8, int* outOffset)
	{

	}

	int CParse::ParseObject(uint8_t *src, const int srcLen, Object& obj, int* outOffset)
	{

	}

	int CParse::ParseMovieClip(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseNull(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseUndefined(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseReference(uint8_t *src, const int srcLen, Reference &refer, int* outOffset)
	{

	}

	int CParse::ParseEcmaArray(uint8_t *src, const int srcLen, ECMA_Array &ecma, int* outOffset)
	{

	}

	int CParse::ParseObjectEnd(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseStrictArray(uint8_t *src, const int srcLen, StrictArray& strictArray, int* outOffset)
	{

	}

	int CParse::ParseDate(uint8_t *src, const int srcLen, Date& date, int* outOffset)
	{

	}

	int CParse::ParseLongString(uint8_t *src, const int srcLen, LongString &utf8, int* outOffset)
	{

	}

	int CParse::ParseUnsupported(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseRecordSet(uint8_t *src, const int srcLen, int* outOffset)
	{

	}

	int CParse::ParseXmlDocument(uint8_t *src, const int srcLen, XML_Document &utf8, int* outOffset)
	{

	}

	int CParse::ParseTypeObject(uint8_t *src, const int srcLen, TypedObject &typeObject, int* outOffset)
	{

	}
};



/*
void UTF8_free(UTF8 &utf8)
{
	if (utf8.buff)	delete[] utf8.buff;
	utf8.buff = NULL;
	utf8.buffLength = 0;
}

void AMF0Object_free(AMF0Object &amfObject)
{
	int i = 0;
	for (i = 0;i < amfObject.MemCount;i++)
	{
		UTF8_free(amfObject.pMems[i].name);
		AMF0Data_free(amfObject.pMems[i].value);
	}

	if(amfObject.pMems)
		delete[] amfObject.pMems;
	amfObject.pMems = NULL;
	amfObject.MemCount = 0;
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
		delete amfData.pNumber;
		amfData.pNumber = NULL; 
		break;
	case AMF0Type::BOOLEAN:
		delete amfData.pBoolean;
		amfData.pBoolean = NULL;
		break;
	case AMF0Type::STRING:
		UTF8_free(*(amfData.pString));
		amfData.pString = NULL;
		break;
	case AMF0Type::OBJECT:
		AMF0Object_free(*(amfData.pObject));
		amfData.pObject = NULL;
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
		AMF0EcmaArray_free(*(amfData.pEcmaArray));
		amfData.pEcmaArray = NULL;
		break;
	case AMF0Type::OBJECT_END:
		break;
	case AMF0Type::STRICT_ARRAY:
		AMF0StrictArray_free(*(amfData.pStrictArray));
		amfData.pStrictArray = NULL;
		break;
	case AMF0Type::DATE:
		delete amfData.pDate;
		amfData.pDate = NULL;
		break;
	case AMF0Type::LONG_STRING:
		UTF8_free(*(amfData.pStringLong));
		amfData.pStringLong = NULL;
		break;
	case AMF0Type::UNSUPPORTED:
		break;
	case AMF0Type::RECORDSET:
		break;
	case AMF0Type::XML_DOCUMENT:
		UTF8_free(*(amfData.pXmlDocument));
		amfData.pXmlDocument = NULL;
		break;
	case AMF0Type::TYPE_OBJECT:
		AMF0TypeObject_free(*(amfData.pTypeObject));
		amfData.pTypeObject = NULL;
		break;

	default:
		break;
	}
}

AMF0Data* amf0_malloc(AMF0Type aType)
{
	AMF0Data *pamf = NULL;
	pamf = new AMF0Data;
	memset(pamf, 0, sizeof(AMF0Data));
	pamf->dType = aType;
	switch (aType)
	{
	case AMF0Type::NUMBER:
		pamf->pNumber = new DOUBLE;
		break;
	case AMF0Type::BOOLEAN:
		pamf->pBoolean = new U8;
		break;
	case AMF0Type::STRING:
		pamf->pString = new UTF8;
		break;
	case AMF0Type::OBJECT:
		pamf->pObject = new AMF0Object;
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
		pamf->pEcmaArray = new AMF0EcmaArray;
		break;
	case AMF0Type::OBJECT_END:
		break;
	case AMF0Type::STRICT_ARRAY:
		pamf->pStrictArray = new AMF0StrictArray;
		break;
	case AMF0Type::DATE:
		pamf->pDate = new DOUBLE;
		break;
	case AMF0Type::LONG_STRING:
		pamf->pStringLong = new UTF8;
		break;
	case AMF0Type::UNSUPPORTED:
		break;
	case AMF0Type::RECORDSET:
		break;
	case AMF0Type::XML_DOCUMENT:
		pamf->pXmlDocument = new UTF8;
		break;
	case AMF0Type::TYPE_OBJECT:
		pamf->pTypeObject = new AMF0TypeObject;
		break;

	default:
		break;
	}
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
	int offset = 0;

	AMF0Data *amf = NULL;

	while (ptr < end)
	{
		amf = CAMF0::Parse(ptr,end-ptr,&offset);
		if (amf == NULL)
			return SAR_FAILURE;
		ptr += offset;
		m_Amfs.push_back(amf);
	}
	return SAR_OK;
}

AMF0Data* CAMF0::Parse(uint8_t *pData, const int dataLen, int* outOffset)
{
	if (pData == NULL || dataLen == 0 )
		return NULL;

	uint8_t marker = 0x00;
	uint8_t *ptr = pData;
	const uint8_t* start = pData, *end = pData + dataLen - 1;
	int ret = SAR_FAILURE;
	int offset = 0;

	AMF0Data* pamf = NULL;
	marker = *ptr;
	ptr += 1;
	switch (marker)
	{
	case AMF0Type::NUMBER:
		pamf = amf0_malloc(AMF0Type::NUMBER);
		ret = CAMF0::ParseNumber(ptr,end-ptr,*(pamf->pNumber),&offset);
		break;
	case AMF0Type::BOOLEAN:
		pamf = amf0_malloc(AMF0Type::BOOLEAN);
		ret = CAMF0::ParseBoolean(ptr, end - ptr, *(pamf->pBoolean), &offset);
		break;
	case AMF0Type::STRING:
		pamf = amf0_malloc(AMF0Type::STRING);
		ret = CAMF0::ParseString(ptr,end-ptr,*(pamf->pString),&offset);
		break;
	case AMF0Type::OBJECT:
		pamf = amf0_malloc(AMF0Type::OBJECT);
		ret = CAMF0::ParseObject(ptr,end-ptr,*(pamf->pObject),&offset);
		break;
	case AMF0Type::MOVIECLIP:
		ret = CAMF0::ParseMovieClip(ptr,end-ptr,&offset);
		break;
	case AMF0Type::NULL_MARKER:
		ret = CAMF0::ParseNull(ptr,end-ptr,&offset);
		break;
	case AMF0Type::UNDEFINED:
		ret = CAMF0::ParseUndefined(ptr,end-ptr,&offset);
		break;
	case AMF0Type::REFERENCE:
		pamf = amf0_malloc(AMF0Type::REFERENCE);
		ret = CAMF0::ParseReference(ptr,end-ptr,*(pamf->pReference),&offset);
		break;
	case AMF0Type::ECMA_ARRAY:
		pamf = amf0_malloc(AMF0Type::ECMA_ARRAY);
		ret = CAMF0::ParseEcmaArray(ptr,end-ptr,*(pamf->pEcmaArray),&offset);
		break;
	case AMF0Type::OBJECT_END:
		ret = CAMF0::ParseObjectEnd(ptr,end-ptr,&offset);
		break;
	case AMF0Type::STRICT_ARRAY:
		pamf = amf0_malloc(AMF0Type::STRICT_ARRAY);
		ret = CAMF0::ParseStrictArray(ptr,end-ptr,*(pamf->pStrictArray),&offset);
		break;
	case AMF0Type::DATE:
		pamf = amf0_malloc(AMF0Type::DATE);
		ret = CAMF0::ParseDate(ptr,end-ptr,*(pamf->pDate),&offset);
		break;
	case AMF0Type::LONG_STRING:
		pamf = amf0_malloc(AMF0Type::LONG_STRING);
		ret = CAMF0::ParseLongString(ptr,end-ptr,*(pamf->pStringLong),&offset);
		break;
	case AMF0Type::UNSUPPORTED:
		ret = CAMF0::ParseUnsupported(ptr,end-ptr,&offset);
		break;
	case AMF0Type::RECORDSET:
		ret = CAMF0::ParseRecordSet(ptr,end-ptr,&offset);
		break;
	case AMF0Type::XML_DOCUMENT:
		pamf = amf0_malloc(AMF0Type::XML_DOCUMENT);
		ret = CAMF0::ParseXmlDocument(ptr,end-ptr,*(pamf->pXmlDocument),&offset);
		break;
	case AMF0Type::TYPE_OBJECT:
		pamf = amf0_malloc(AMF0Type::TYPE_OBJECT);
		ret = CAMF0::ParseTypeObject(ptr,end-ptr,*(pamf->pTypeObject),&offset);
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;

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
	const uint8_t* start = pData, *end = pData + dataLen - 1;

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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
	
	int ret = SAR_FAILURE;
	uint8_t three[3] = {0};
	int offset = 0;
	int i = 0;
	
	AMF0Data *pValue = NULL;
	vector<ObjectMember> mems;
	ObjectMember mem;
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


		pValue = CAMF0::Parse(ptr,end-ptr,&offset);
		if (pValue == NULL)
			goto PARSE_ERR;
		ptr += offset;

		mem.name = name;
		mem.value = *pValue;
		mems.push_back(mem);
	}

	amfObj.MemCount = mems.size();
	amfObj.pMems = new ObjectMember[amfObj.MemCount];
	for (i=0;i<amfObj.MemCount;i++)
		amfObj.pMems[i] = mems.at(i);
	*outOffset = ptr - start;

	return SAR_OK;

PARSE_ERR:
	for (i = 0;i<mems.size(); i++)
	{
		AMF0Data_free(mems.at(i).value);
		UTF8_free(mems.at(i).name);
	}
	mems.clear();
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
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
		pValue = Parse(ptr,end-ptr,&offset);
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;
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
	const uint8_t* start = pData, *end = pData + dataLen - 1;

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
	const uint8_t* start = pData, *end = pData + dataLen - 1;

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
*/