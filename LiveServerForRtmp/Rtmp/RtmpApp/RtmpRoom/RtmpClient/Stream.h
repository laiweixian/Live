#pragma once

class IStreamEvent
{
protected:
	IStreamEvent() = default;
	virtual ~IStreamEvent() = default;
public:
	virtual int OnReceive(const char* buf, const int bufLen) = 0;
	virtual int OnClose() = 0;
	virtual int OnError() = 0;
};

class IStreamCall
{
protected:
	IStreamCall() = default;
	virtual ~IStreamCall() = default;
public:
	virtual int Open() = 0;
	virtual int Read(char* outBuf,int *outLen) = 0;
	virtual int Close() = 0;
};
