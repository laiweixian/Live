#include "SocketClient.h"

#define BUFF_LEN	1024

CSocketClient::CSocketClient(SOCKET so,sockaddr_in addr):m_Socket(so), m_Addr(addr)
{
	InitReadBuff();
	InitWriteBuff();
}

CSocketClient::~CSocketClient()
{
	
}



int CSocketClient::InitReadBuff()
{
	m_Reader->totalLen = BUFF_LEN;
	m_Reader->buff = new uint8_t[BUFF_LEN];
	memset(m_Reader->buff,0,BUFF_LEN);
	m_Reader->length = 0;
	m_Reader->state = SocketState::READ_WAIT;
	return 0;
}

int CSocketClient::InitWriteBuff()
{
	m_Writer->totalLen = BUFF_LEN;
	m_Writer->buff = new uint8_t[BUFF_LEN];
	memset(m_Writer->buff, 0, BUFF_LEN);
	m_Writer->length = 0;
	m_Writer->state = SocketState::WARITEABLE;
	return 0;
}

CSocketClient::SocketState CSocketClient::CheckRead()
{
	int length ;
	byte *ptr  = m_Reader->buff;
	int receSize  = m_Reader->totalLen;
	int errorCode;

	if (m_Reader->state != SocketState::READ_WAIT)
		return m_Reader->state;

	length = ::recv(m_Socket, (char*)ptr, receSize, 0);
	if (length == 0)
	{
		m_Reader->state = SocketState::CLOSE;
	}
	else if (length > 0)
	{
		m_Reader->state = SocketState::READABLE;
		m_Reader->length += length;
	}
	else
	{
		errorCode = WSAGetLastError();
		if (errorCode == WSAEWOULDBLOCK)
		{
			m_Reader->state = SocketState::READ_WAIT;
		}
			
		else 
			m_Reader->state = SocketState::ERR_SOCK;
	}

	return m_Reader->state;
}

CSocketClient::SocketState CSocketClient::CheckWrite()
{
	return m_Writer->state;
}

int CSocketClient::Read(char *src, size_t srcSize, int *outSize)
{
	int length = 0;

	if (m_Reader->state != READABLE)
		return 0;

	if (srcSize >= m_Reader->length)
	{
		length = m_Reader->length;
		memcpy(src,m_Reader->buff, length);

		memset(m_Reader->buff,0,length);
		m_Reader->length = 0;
		m_Reader->state = READ_WAIT;
	}
	else
	{	
		length = srcSize;
		memcpy(src, m_Reader->buff, length);

		//
		byte *temp = new byte[m_Reader->length - length];
		memcpy(temp,m_Reader->buff+length, m_Reader->length - length);

		memset(m_Reader->buff, 0, length);
		memcpy(m_Reader->buff,temp, m_Reader->length - length);
		m_Reader->length -= length;
		m_Reader->state = READABLE;

		delete[] temp;
	}


	return length;
}

int CSocketClient::Write(char *src, size_t srcSize, int *outSize)
{
	if (m_Reader->state != WARITEABLE)
		return -1;

	int length ;

	length = send(m_Socket, src, srcSize ,0);
	return length;
}	

int CSocketClient::Close()
{
	return 0;
}