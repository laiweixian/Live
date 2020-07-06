#include "AMF0.h"
using namespace AMF0;

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off  > end ) goto fail;

void AMF0::AllocDataBuff(Data& data, uint8_t* src, uint64_t len)
{
	data.len = len;
	data.buf = new uint8_t[len];

	memcpy(data.buf,src,len);
}

bool AMF0::IsNumber(Data& data)
{
	return data.marker == MARKER_NUMBER;
}

bool AMF0::IsBoolean(Data& data)
{
	return data.marker == MARKER_BOOLEAN;
}

bool AMF0::IsString(Data& data)
{
	return (data.marker == MARKER_STRING || data.marker == MARKER_LONG_STRING);
}

bool AMF0::IsObject(Data& data)
{
	return (data.marker == MARKER_OBJECT);
}

bool AMF0::IsReference(Data& data)
{
	return (data.marker == MARKER_REFERENCE);
}

bool AMF0::IsECMA_Array(Data& data)
{
	return (data.marker == MARKER_ECMA_ARRAY);
}

bool AMF0::IsStrictArray(Data& data)
{
	return (data.marker == MARKER_STRICT_ARRAY);
}

bool AMF0::IsDate(Data& data)
{
	return (data.marker == MARKER_DATE);
}

bool AMF0::IsXMLDocument(Data& data)
{
	return (data.marker == MARKER_XML_DOCUMENT);
}

bool AMF0::IsTypeObject(Data& data)
{
	return (data.marker == MARKER_TYPE_OBJECT);
}

int AMF0::ParseUTF8(uint8_t* src, uint32_t len, UTF8& utf8, int *outLen)
{
	const uint8_t* start = src, *end = src + len;
	uint8_t *ptr = src;
	bool c1 = false , c2 = false, c3 = false, c4 = false;
	int charLen = 0;
	uint16_t count = 0;
	int i = 0;

	CHECK_OFFSET(start, end, ptr, 2)
	count = ::BigToHost16(ptr);
	ptr += 2;

	for (i = 0;i < count;i++)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || (*ptr) == 0xf4;
		
		if (c1)
			charLen = 1;
		else if (c2)
			charLen = 2;
		else if (c3)
			charLen = 3;
		else if (c4)
			charLen = 4;

		CHECK_OFFSET(start, end, ptr, charLen)
		ptr += charLen;
	}

	utf8.len = ptr -(start+2);
	utf8.buf = new uint8_t[utf8.len];
	memcpy(utf8.buf,start+2,utf8.len);

	*outLen = ptr - start;
	return AMF0_OK;

fail:
	*outLen = 0;
	return AMF0_FAILURE;
}

int AMF0::ParseUTF8Long(uint8_t* src, uint32_t len, UTF8& utf8, int *outLen)
{
	const uint8_t* start = src, *end = src + len;
	uint8_t *ptr = src;
	bool c1 = false, c2 = false, c3 = false, c4 = false;
	int charLen = 0;
	uint32_t count = 0;
	int i = 0;

	CHECK_OFFSET(start, end, ptr, 4)
	count = ::BigToHost32(ptr);
	ptr +=4;

	for (i = 0;i < count;i++)
	{
		c1 = (*ptr) >= 0x00 && (*ptr) <= 0x7f;
		c2 = (*ptr) >= 0xc2 && (*ptr) <= 0xdf;
		c3 = (*ptr) == 0xe0 || ((*ptr) >= 0xe1 && (*ptr) <= 0xec) || (*ptr) == 0xed || ((*ptr) >= 0xee && (*ptr) <= 0xef);
		c4 = (*ptr) == 0xf0 || ((*ptr) >= 0xf1 && (*ptr) <= 0xf3) || (*ptr) == 0xf4;

		if (c1)
			charLen = 1;
		else if (c2)
			charLen = 2;
		else if (c3)
			charLen = 3;
		else if (c4)
			charLen = 4;

		CHECK_OFFSET(start, end, ptr, charLen)
		ptr += charLen;
	}

	utf8.len = ptr - (start + 4);
	utf8.buf = new uint8_t[utf8.len];
	memcpy(utf8.buf, start + 4, utf8.len);

	*outLen = ptr - start;
	return AMF0_OK;

fail:
	*outLen = 0;
	return AMF0_FAILURE;
}


bool AMF0::CompareUtf8(UTF8& u1, UTF8& u2)
{
	const int length = u1.len;
	int i = 0;
	bool same = true;

	if (u2.len != u1.len)
		return false;

	for (i=0;i<length;i++)
		same = (same && u1.buf[i] == u2.buf[i]);
	return same;
}

void AMF0::CopyData(Data& dst, Data& src)
{
	dst.len = src.len;
	dst.buf = new uint8_t[dst.len];
	memcpy(dst.buf,src.buf,dst.len);
}

void AMF0::Utf8Free(UTF8** ppUtf8)
{
	UTF8* p = *ppUtf8;
	if (p->buf) delete[] p->buf;
	p->buf = NULL;
	p->len = 0;

	delete p;
	p = NULL;
}

void AMF0::DataFree(Data** ppData)
{
	if ((*ppData)->buf) delete[] (*ppData)->buf;
	(*ppData)->buf = NULL;
	(*ppData)->len = 0;
	delete (*ppData);
	(*ppData) = NULL;
}

Data* AMF0::DataAlloc()
{
	Data* pdata = new Data;
	pdata->buf = NULL;
	pdata->len = 0;
	pdata->marker = MARKER_NONE;
	return pdata;
}

UTF8* AMF0::Convert(const char* c)
{
	const int length = strlen(c);
	UTF8 * p = new UTF8;
	
	if (length == 0)
		return NULL;

	p->buf = new uint8_t[length];
	p->len = length;
	memcpy(p->buf,c,length);
	return p;
}

char* AMF0::CreateNumber(double data, int* outSize)
{
	char *buf = NULL, *ptr = NULL;
	int bufSize = 0;
	char marker = MARKER_NUMBER;
	double number;

	number = BigToHostDouble(data);
	
	bufSize = 1 + 8;
	buf = new char[bufSize];
	ptr = buf;

	memcpy(ptr, &marker, 1);	ptr += 1;
	memcpy(buf,&number, 8);

	*outSize = bufSize;
	return buf;
}

char* AMF0::CreateBoolean(bool data, int* outSize)
{
	char *buf = NULL, *ptr = NULL;
	int bufSize = 0;
	char marker = MARKER_BOOLEAN;

	bufSize = 1 + 1;
	buf = new char[bufSize];

	ptr = buf;
	memcpy(ptr, &marker, 1);	ptr += 1;
	memcpy(ptr, &data, 1);	ptr += 1;
	
	*outSize = bufSize;
	return buf;
}

char* AMF0::CreateString(char* str, int strSize, int* outSize)
{
	char *buf = NULL, *ptr = NULL,*utf8Buf = NULL;
	int bufSize = 0 , utf8BufSize = 0;
	char marker = MARKER_STRING;
	
	utf8Buf = CreateUtf8(str,strSize,&utf8BufSize);

	bufSize = 1 + utf8BufSize;
	buf = new char[bufSize];

	ptr = buf;
	memcpy(ptr,&marker,1);	ptr+=1;
	memcpy(ptr,utf8Buf,utf8BufSize); ptr += utf8BufSize;

	delete[] utf8Buf;	utf8Buf = NULL;

	*outSize = bufSize;
	return buf;
}

char* AMF0::CreateUtf8(char* str, int strSize, int *outSize)
{
	char *buf = NULL, *ptr = NULL;
	int bufSize = 0;
	uint16_t count = strSize , bigCount ;

	bigCount = HostToBig16(count);

	bufSize = 2 + strSize;
	buf = new char[bufSize];

	ptr = buf;
	memcpy(ptr,&bigCount,2);	ptr += 2;
	memcpy(ptr,str,strSize);	ptr += strSize;

	*outSize = bufSize;
	return buf;
}

char* AMF0::CreateObjectChild(char* utf8Name, int utf8NameSize, char* value, int valueSize, int* outSize)
{
	char *buf = NULL, *ptr = NULL, *utf8Buf = NULL;
	int bufSize = 0 , utf8BufSize = 0;

	utf8Buf = CreateUtf8(utf8Name,utf8NameSize,&utf8BufSize);
	
	bufSize = utf8BufSize + valueSize;
	buf = new char[bufSize];

	ptr = buf;
	memcpy(ptr,utf8Buf,utf8BufSize);	ptr += utf8BufSize;
	memcpy(ptr,value,valueSize);		ptr += valueSize;
	
	delete[] utf8Buf;

	*outSize = bufSize;
	return buf;
}

char* AMF0::CreateObject(char** childs, int* childSize, int count, int* outSize)
{
	char *buf = NULL, *ptr = NULL;
	int bufSize = 0;
	char marker = MARKER_OBJECT;
	char end[3] = { 0x00,0x00,MARKER_OBJECT_END };
	int i = 0;

	bufSize += 1;
	for (i = 0; i < count; i++)
		bufSize += childSize[i];
	bufSize += 3;
	buf = new char[bufSize];

	ptr = buf;
	memcpy(ptr, &marker, 1);	ptr += 1;
	for (i = 0; i < count; i++)
	{
		memcpy(ptr,childs[i],childSize[i]);
		ptr += childSize[i];
	}
	memcpy(ptr,end,3);

	*outSize = bufSize;
	return buf;	
}
