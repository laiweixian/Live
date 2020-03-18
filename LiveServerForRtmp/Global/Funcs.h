#pragma once


#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>

static uint32_t GetTimestamp()
{
	timeb rawTime;
	ftime(&rawTime);
	return rawTime.time * 1000 + rawTime.millitm;
}

static uint16_t BigToHost16(void* src)
{
	uint16_t srcNumber = 0;
	memcpy(&srcNumber,src,2);

	
	return ntohs(srcNumber);
}

static uint32_t BigToHost24(void* src)
{
	uint32_t srcNumber = 0;
	memcpy(&srcNumber,src,3);

	return ntohl(srcNumber);
}

static uint32_t BigToHost32(void* src)
{
	uint32_t srcNumber = 0;
	memcpy(&srcNumber, src, 4);

	return ntohl(srcNumber);
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

static double BigToHostDouble(void *src,const int srcLen)
{
	double number = 0 ;

	memcpy(&number,src,srcLen);

	return number;
}