#include "AMF0.h"
using namespace AMF0;

#define CHECK_OFFSET(start,end,ptr,off)	if (ptr + off  >= end ) goto fail;

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