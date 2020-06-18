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
	uint16_t dstNum = 0;

	dstNum = src[1] * pow(0xff,0)+\
			 src[0] * pow(0xff,1);
	


	return dstNum;
}

static uint32_t BigToHost24(uint8_t* src)
{
	uint32_t dstNumber ;

	dstNumber = src[2] * pow(0xff,0)+\
				src[1] * pow(0xff,1)+\
				src[0] * pow(0xff,2);
	return dstNumber;
}

static uint32_t BigToHost32(uint8_t* src)
{
	uint32_t dstNumber;

	dstNumber = src[3] * pow(0xff,0)+ \
				src[2] * pow(0xff,1)+ \
				src[1] * pow(0xff,2)+\
				src[0] * pow(0xff,3);

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

