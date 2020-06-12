#pragma once

#include "stdafx.h"

class CSocketClient
{
public:
	enum SocketState { NONE,READ_WAIT,READABLE,WRITE_WAIT,WARITEABLE,CLOSE,ERR_SOCK};
	CSocketClient(SOCKET so, sockaddr_in addr);
	~CSocketClient();

public:
	SocketState CheckRead();
	SocketState CheckWrite();
	int Read( char *src, size_t srcSize);
	int Write( char *src, size_t srcSize);
	int Close();

private:

	int InitReadBuff();
	int InitWriteBuff(); 
	
private:
	struct Buffer
	{
		uint8_t *buff;
		uint32_t totalLen;
		uint32_t length;
		SocketState state;
	};

	SOCKET m_Socket;
	sockaddr_in m_Addr;

	Buffer *m_Reader;
	Buffer *m_Writer;
};
