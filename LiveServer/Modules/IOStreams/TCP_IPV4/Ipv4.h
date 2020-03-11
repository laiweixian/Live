#pragma once
#include "Modules/IOStreams/BaseIOStream.h"

#define IPV4_NAME "ipv4"
//default element 
#define IPV4_IP	""
#define IPV4_PORT	0	
#define IPV4_MAX_CONNECT 100
#define IPV4_TIME_OUT	500	//millisecond (ms)
#define IPV4_EVENT_NAME	""

class CIPV4 final : public CBaseIOStream
{
public:
	CIPV4();
	~CIPV4();

public:
	ULONG Init();
	ULONG Run();
	ULONG Release();
	const char* GetIOStreamName();
	BOOL Active();

	ULONG Open();
	ULONG Read(const int ioID, char* dst, const int dstLen);
	ULONG Write(const int ioID, char* dst, const int dstLen);
	ULONG Seek(const int ioID, EIOPos pos, const int offset);
	ULONG Close(const int ioID);

private:
	ULONG InitSocket();

private:
	BOOL m_Active;

	char m_Ip[100];
	int m_Port;
	int m_MaxConnect;
	int m_TimeOut;
	char m_EventName[100];
	

	int m_ListenSocket;
	vector<int> m_ConnectSocket;
};
