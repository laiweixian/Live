#pragma once

#include "stdafx.h"
#include "Buffer.h"


class CSocketClient
{
public:
	
	CSocketClient(SOCKET so, sockaddr_in addr);
	~CSocketClient();

public:
	int CheckRead();
	int Read(uint8_t *src, size_t srcSize);
	int Write(uint8_t *src, size_t srcSize);
	int Close();
private:
	SOCKET m_Socket;
	sockaddr_in m_Addr;

	CBuffer  m_Reader;
	
};
