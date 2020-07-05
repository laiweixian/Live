#pragma once

#include <stdint.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>
#include <math.h>

struct RtmpUrl
{
	char addr[200];
	char port[200];
	char app[200];
	char instance[200];
};

RtmpUrl* ParseRtmpUrl(char* rtmpurl);
uint32_t GetTimestamp();
uint16_t BigToHost16(uint8_t* src);
uint32_t BigToHost24(uint8_t* src);
uint32_t BigToHost32(uint8_t* src);
uint16_t HostToBig16(uint16_t src);
uint32_t HostToBig24(uint32_t src);
uint32_t HostToBig32(uint32_t src);
double   HostToBigDouble(double src);
double   BigToHostDouble(double src);
void GenRamdomByte(char* buff, const int buffLen);