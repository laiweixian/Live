#pragma once

class IPublishEvent
{
protected:
	IPublishEvent() = default;
	virtual ~IPublishEvent() = default;

public:
	virtual int OnPlayerEnter() = 0;
	virtual int OnPlayerLeave() = 0;
};

class IPublishCall
{
protected:
	IPublishCall() = default;
	virtual ~IPublishCall() = default;

public:
	virtual int CreateRoom(string name) = 0;
	virtual int DestroyRoom(int roomId) = 0;
	virtual int PublishVideo(int roomId,const char* buf,const int bufLen) = 0;
	virtual int PublishAudio(int roomId, const char* buf, const int bufLen) = 0;
	virtual int PublishMsg(int roomId, const char* buf, const int bufLen) = 0;
};
