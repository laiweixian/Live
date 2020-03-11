#pragma once


class CIOMessage
{
protected:
	virtual ~CIOMessage() = default;
public:
	CIOMessage() = default;
	virtual void OnConnect(const int ioId) = 0;
	virtual void OnData(const int ioId) = 0;
	virtual void OnClose(const int ioId) = 0;
};

class CIOInterface
{
public:
	CIOInterface() = default;
	virtual ~CIOInterface() = default;

	virtual ULONG Open(const char* ip, const int port, CIOMessage* pMsg) = 0;
	virtual ULONG Read(const int ioId,char* buf,const int bufLen,int *outLen) = 0;
	virtual ULONG Write(const int ioId,char* buf, const int bufLen, int *outLen) = 0;
	virtual ULONG Close(const int ioId) = 0;
};
