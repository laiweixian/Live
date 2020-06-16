#pragma once


#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

static uint32_t GetTimestamp()
{
	timeb rawTime;
	ftime(&rawTime);
	return rawTime.time * 1000 + rawTime.millitm;
}

static uint16_t BigToHost16(uint8_t* src)
{
	uint8_t number[2] = { 0 };
	uint8_t dst[2] = { 0 };
	uint16_t dstNum = 0;

	memcpy(number,src,2);

	dst[0] = number[1];
	dst[1] = number[0];

	memcpy(&dstNum,dst,2);
	return dstNum;
}

static uint32_t BigToHost24(uint8_t* src)
{
	uint8_t number[4] = {0};
	uint8_t dst[4] = { 0 };
	uint32_t dstNumber ;

	memcpy(number,src,3);
	
	dst[0] = number[3];
	dst[1] = number[2];
	dst[2] = number[1];
	dst[3] = number[0];

	memcpy(&dstNumber,dst,4);
	return dstNumber;
}

static uint32_t BigToHost32(uint8_t* src)
{
	uint8_t number[4] = { 0 };
	uint8_t dst[4] = { 0 };
	uint32_t dstNumber;

	memcpy(number, src,4);

	dst[0] = number[3];
	dst[1] = number[2];
	dst[2] = number[1];
	dst[3] = number[0];

	memcpy(&dstNumber, dst, 4);

	return dstNumber;
}

static uint16_t HostToBig16(uint16_t src)
{
	return htons(src);
}

static uint32_t HostToBig24(uint32_t src)
{
	return htonl(src);
}

static uint32_t HostToBig32(uint32_t src)
{
	return htonl(src);
}

static void GenRamdomByte(char* buff, const int buffLen)
{
	int i;
	int s;
	char c;
	
	for (i=0;i<buffLen;i++)
	{
		srand((unsigned)time(NULL));
		s = rand()%256;
		c = 0x00 + s;

		memcpy(buff+i,&c,1);
	}
}

