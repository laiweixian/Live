#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GMT_SM2_P	"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"
#define GMT_SM2_A	"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"
#define GMT_SM2_B	"28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"
#define GMT_SM2_N	"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"
#define GMT_SM2_XG	"32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
#define GMT_SM2_YG	"BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"

static unsigned char* hex2BigInteger(const char* str, int* outSize)
{
	int i = 0;
	int length = strlen(str);
	unsigned char curChar = 0x00;
	unsigned char ch0, ch1;

	if (length % 2 != 0)
		return NULL;

	unsigned char *bigNum = (unsigned char*)calloc(length, sizeof(char));
	int index = 0;
	unsigned char *buf = NULL;
	int bufSize = 0;

	for (i = 0;i < length;i = i + 2)
	{
		memcpy(&ch0, str + i, 1);
		memcpy(&ch1, str + i + 1, 1);

		if (ch0 >= '0'&&ch0 <= '9')
			ch0 = ch0 - '0';
		else if (ch0 >= 'a'&&ch0 <= 'f')
			ch0 = ch0 - 'a' + 10;
		else if (ch0 >= 'A'&&ch0 <= 'F')
			ch0 = ch0 - 'A' + 10;
		else
			return NULL;

		if (ch1 >= '0'&&ch1 <= '9')
			ch1 = ch1 - '0';
		else if (ch1 >= 'a'&&ch1 <= 'f')
			ch1 = ch1 - 'a' + 10;
		else if (ch1 >= 'A'&&ch1 <= 'F')
			ch1 = ch1 - 'A' + 10;
		else
			return NULL;

		ch0 = ch0 * 16;
		curChar = ch0 + ch1;
		memcpy(bigNum + index, &curChar, 1);
		index++;
	}

	bufSize = index;
	buf =(unsigned char*) calloc(bufSize, 1);
	memcpy(buf, bigNum, bufSize);

	free(bigNum);

	*outSize = bufSize;
	return buf;
}