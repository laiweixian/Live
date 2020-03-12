#pragma once


class IIOMsg
{
protected:
	virtual ~IIOMsg() = default;
public:
	IIOMsg() = default;

	virtual void OnConnect(const int ioId) = 0;
	virtual void OnReceive(const int ioId) = 0;
	virtual void OnSend(const int ioId) = 0;
	virtual void OnClose(const int ioId) = 0;
	virtual void OnError(const int ioId) = 0;
};

class IIO
{
protected:
	virtual ~IIO() = default;
public:
	IIO() = default;

	virtual int Open() = 0;
	virtual int Read(const int ioId,char *buff,const int buffLen) = 0;
	virtual int Write(const int ioId,char *buff,const int buffLen) = 0;
	virtual int Close(const int ioId) = 0;
};


