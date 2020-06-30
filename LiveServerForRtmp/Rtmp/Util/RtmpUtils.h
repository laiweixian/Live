#pragma once

struct RtmpUrl
{
	char addr[200];
	char port[200];
	char app[200];
	char instance[200];
};

RtmpUrl* ParseRtmpUrl(char* rtmpurl);

