#pragma once

class IPublish
{
protected:
	IPublish() = default;
	~IPublish() = default;

public:
	virtual int Disband() = 0;
	virtual int BroadcastVideo(const char* buf, const int bufLen) = 0;
	virtual int BroadcastAudio(const char* buf, const int bufLen) = 0;
	virtual int BroadcastMsg(void* ctx) = 0;
};

