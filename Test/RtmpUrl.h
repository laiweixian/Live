#pragma once
#include "stdafx.h"
#include <string.h>

#pragma warning(disable:4996)

#define RTMP_URL "rtmp://localhost:1935/testapp/instance1";
#define RTMP_URL2 "rtmp://localhost/testapp/instance1";

struct RtmpUrl
{
	char addr[200];
	char port[200];
	char app[200];
	char instance[200];
};

static uint32_t Str2Int(const char* s)
{
	return atoi(s);
}

//rtmp://localhost:1935/testapp/instance1 (±ê×¼ÎÄµµ)
static RtmpUrl* ParseRtmpUrl(char* rtmp)
{
	RtmpUrl* url = new RtmpUrl;
	memset(url,0,sizeof(RtmpUrl));
	char *ptr = rtmp,*ptr0 = NULL,*ptr1 = NULL ;
	const char *end = rtmp + strlen(rtmp);
	const char *needle0 = "rtmp://" ,*needle1=":",*needle2="/";
	char port[100] = {0},addr[100]={0},app[100] = {0},instance[100] = {0};
	
	ptr0 = strstr(ptr, needle0);
	if (ptr0 == NULL)
		goto fail;
	ptr += strlen(needle0);

	//address ,port
	ptr0 = strstr(ptr,needle1);
	ptr1 = strstr(ptr,needle2);
	if (ptr0 != NULL && ptr1 > ptr0)
	{
		memcpy(addr,ptr,ptr0-ptr);
		memcpy(port,ptr0+1,ptr1-ptr0-1);

	}
	else if (ptr1 == NULL)
	{
		goto fail;
	}
	else
	{
		memcpy(addr,ptr,ptr1-ptr);
	}

	strcpy(url->addr,addr);
	strcpy(url->port,port);
	ptr = ptr1+1;
	

	//app
	ptr0 = strstr(ptr, needle2);
	if (ptr0 == NULL)
		return NULL;
	memcpy(app,ptr,ptr0-ptr);
	strcpy(url->app,app);
	ptr = ptr0 + 1;

	//instance
	memcpy(instance, ptr, end - ptr);
	strcpy(url->instance,instance);
	
	return url;

fail:
	if (url)	delete url;
	url = NULL;
	return NULL;
}


