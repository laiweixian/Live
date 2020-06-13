#pragma once

#include "stdafx.h"

class CSocketClient
{
public:
	struct Buffer
	{
		uint8_t *buff;
		uint32_t totalLen;

		uint8_t  *ptr;
		uint32_t length;
	};
	CSocketClient(SOCKET so, sockaddr_in addr);
	~CSocketClient();

public:
	int CheckRead();
	int CheckWrite();
	int Read(char *src, size_t srcSize);
	int Write(char *src, size_t srcSize);
	int Close();

private:
	int InitReadBuff();
	int InitWriteBuff(); 

	int AppendReadBuff(byte* src,int length);
	int GetReadBufLength();
	int CopyReadBuf(char *src, size_t srcSize);
	int ExtendReadBuf();
	int CleanReadBuf();

	/*
	int AppendWriteBuff(byte* src, int length);
	int GetWriteBufLength();
	int ExtendWriteBuf();
	int CleanWriteBuf();
	*/
	
private:
	SOCKET m_Socket;
	sockaddr_in m_Addr;

	Buffer *m_Reader;
	Buffer *m_Writer;
};
