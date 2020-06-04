#pragma once

class IPlayerEvent
{
protected:
	IPlayerEvent() = default;
	virtual ~IPlayerEvent() = default;

public:
	//interface for other class
	virtual int OnVideo(const char* buf, const int bufLen) = 0;
	virtual int OnAudio(const char* buf, const int bufLen) = 0;
	virtual int OnMsg(const char* buf, const int bufLen) = 0;
	virtual int OnDisband() = 0;
};

class IPlayerCall
{
protected:
	IPlayerCall() = default;
	virtual ~IPlayerCall() = default;
public:
	virtual int Enter(string roomName) = 0;
	virtual int Leave(string roomName) = 0;
};

