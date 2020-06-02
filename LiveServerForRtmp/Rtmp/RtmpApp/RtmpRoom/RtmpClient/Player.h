#pragma once

class IPlayerNotification
{
protected:
	IPlayerNotification() = default;
	virtual ~IPlayerNotification() = default;

	//interface for other class
	virtual int OnVideo(const char* buf, const int bufLen) = 0;
	virtual int OnAudio(const char* buf, const int bufLen) = 0;
	virtual int OnMsg(const char* buf, const int bufLen) = 0;
	virtual int OnDisband() = 0;
};

class CPlayer : public IPlayerNotification
{
protected:
	CPlayer() = default;
	~CPlayer() = default;

	

};
