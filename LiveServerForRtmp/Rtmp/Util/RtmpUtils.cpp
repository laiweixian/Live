#include "RtmpUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RtmpUrl* ParseRtmpUrl(char* rtmpurl)
{
	RtmpUrl* url = new RtmpUrl;
	memset(url, 0, sizeof(RtmpUrl));
	char *ptr = rtmpurl, *ptr0 = NULL, *ptr1 = NULL;
	const char *end = rtmpurl + strlen(rtmpurl);
	const char *needle0 = "rtmp://", *needle1 = ":", *needle2 = "/";
	char port[100] = { 0 }, addr[100] = { 0 }, app[100] = { 0 }, instance[100] = { 0 };

	ptr0 = strstr(ptr, needle0);
	if (ptr0 == NULL)
		goto fail;
	ptr += strlen(needle0);

	//address ,port
	ptr0 = strstr(ptr, needle1);
	ptr1 = strstr(ptr, needle2);
	if (ptr0 != NULL && ptr1 > ptr0)
	{
		memcpy(addr, ptr, ptr0 - ptr);
		memcpy(port, ptr0 + 1, ptr1 - ptr0 - 1);

	}
	else if (ptr1 == NULL)
	{
		goto fail;
	}
	else
	{
		memcpy(addr, ptr, ptr1 - ptr);
	}

	strcpy(url->addr, addr);
	strcpy(url->port, port);
	ptr = ptr1 + 1;


	//app
	ptr0 = strstr(ptr, needle2);
	if (ptr0 == NULL)
		return NULL;
	memcpy(app, ptr, ptr0 - ptr);
	strcpy(url->app, app);
	ptr = ptr0 + 1;

	//instance
	memcpy(instance, ptr, end - ptr);
	strcpy(url->instance, instance);

	return url;

fail:
	if (url)	delete url;
	url = NULL;
	return NULL;
}

uint32_t GetTimestamp()
{
	timeb rawTime;
	ftime(&rawTime);
	return rawTime.time * 1000 + rawTime.millitm;
}

void GenRamdomByte(char* buff, const int buffLen)
{
	int i;
	int s;
	char c;

	for (i = 0; i < buffLen; i++)
	{
		srand((unsigned)time(NULL));
		s = rand() % 256;
		c = 0x00 + s;

		memcpy(buff + i, &c, 1);
	}
}

uint16_t BigToHost16(uint8_t* src)
{
	uint16_t num = 0;

	num += (*src) * 256;
	num += (*(src + 1)) ;
	return num;
}

uint32_t BigToHost24(uint8_t* src)
{
	uint32_t num = 0;
	
	num += (*src) * 256 * 256;
	num += (*(src + 1)) * 256;
	num += (*(src + 2));
	return num;
}

uint32_t BigToHost32(uint8_t* src)
{
	uint32_t num = 0;

	num += (*src) * 256 * 256 * 256;
	num += (*(src + 1)) * 256 * 256;
	num += (*(src + 2)) * 256;
	num += (*(src + 3)) ;
	return num;
}

uint16_t HostToBig16(uint16_t src)
{
	uint16_t number = 0;
	char* dst = (char*)&number;
	char* cSrc = (char*)&src;

	memcpy(dst, cSrc + 1, 1); 
	memcpy(dst+1,cSrc,1); 
	return number;
}

uint32_t HostToBig24(uint32_t src)
{
	uint32_t number = 0;
	char* dst = (char*)&number;
	char* cSrc = (char*)&src;

	memcpy(dst, cSrc + 3, 1); 
	memcpy(dst+1, cSrc + 2, 1); 
	memcpy(dst+2, cSrc + 1, 1);
	memcpy(dst+3, cSrc + 0, 1); 
	return number;
}

uint32_t HostToBig32(uint32_t src)
{
	uint32_t number = 0;
	char* dst = (char*)&number;
	char* cSrc = (char*)&src;

	memcpy(dst,cSrc+3,1);
	memcpy(dst+1,cSrc+2,1);
	memcpy(dst+2, cSrc + 1, 1);
	memcpy(dst+3, cSrc , 1);
	return number;
}

double   HostToBigDouble(double src)
{
	double dst = 0;
	char* pDst = (char*)&dst;
	char* pSrc = (char*)&src;

	memcpy(pDst, pSrc + 7, 1); pDst += 1;
	memcpy(pDst, pSrc + 6, 1); pDst += 1;
	memcpy(pDst, pSrc + 5, 1); pDst += 1;
	memcpy(pDst, pSrc + 4, 1); pDst += 1;
	memcpy(pDst, pSrc + 3, 1); pDst += 1;
	memcpy(pDst, pSrc + 2, 1); pDst += 1;
	memcpy(pDst, pSrc + 1, 1); pDst += 1;
	memcpy(pDst, pSrc + 0, 1); pDst += 1;

	return dst;
}

double   BigToHostDouble(double src)
{
	double dst = 0;
	char* pDst = (char*)&dst;
	char* pSrc = (char*)&src;

	memcpy(pDst, pSrc + 7, 1); pDst += 1;
	memcpy(pDst, pSrc + 6, 1); pDst += 1;
	memcpy(pDst, pSrc + 5, 1); pDst += 1;
	memcpy(pDst, pSrc + 4, 1); pDst += 1;
	memcpy(pDst, pSrc + 3, 1); pDst += 1;
	memcpy(pDst, pSrc + 2, 1); pDst += 1;
	memcpy(pDst, pSrc + 1, 1); pDst += 1;
	memcpy(pDst, pSrc + 0, 1); pDst += 1;

	return dst;
}