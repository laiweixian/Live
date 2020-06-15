#pragma once

#include "stdafx.h"

struct ClientBuffer
{
	uint8_t *buff;
	uint32_t totalLen;

	uint8_t  *ptr;
	uint32_t length;
};

class CSocketClient
{
public:
	
	CSocketClient(SOCKET so, sockaddr_in addr);
	~CSocketClient();

public:
	int CheckRead();
	int CheckWrite();
	int Read(uint8_t *src, size_t srcSize);
	int Write(uint8_t *src, size_t srcSize);
	int Close();

private:
	int InitReadBuff();
	int InitWriteBuff(); 

	int AppendReadBuff(byte* src,int length);
	int GetReadBufLength();
	int CopyReadBuf(uint8_t *src, size_t srcSize);
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

	ClientBuffer *m_Reader;
	ClientBuffer *m_Writer;
};
