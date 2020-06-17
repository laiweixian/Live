#include "SocketClient.h"
#include "stdafx.h"
#define BUFF_LEN	1024

CSocketClient::CSocketClient(SOCKET so,sockaddr_in addr):m_Socket(so), m_Addr(addr)
{
	
}

CSocketClient::~CSocketClient()
{
	TRACE("addr:%s close\n ", inet_ntoa(m_Addr.sin_addr));
	closesocket(m_Socket);
}





int CSocketClient::CheckRead()
{
	int errorCode = 0;
	int length = 0;
	byte *buf = NULL;

	if (m_Socket == INVALID_SOCKET)
		goto closesock;

	buf =  new byte[1024];
	while (1)
	{
		length = ::recv(m_Socket, (char*)buf, 1024, 0);
		if (length == 0)
		{
			//对端关闭连接
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
			goto closesock;
		}
		else if (length > 0 )
		{
			m_Reader.Append(buf,length);
		}
		else
		{
			errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
				goto data;
			else
			{
				closesocket(m_Socket);
				m_Socket = INVALID_SOCKET;
				goto closesock;
			}
		}
	}

	return -1;

closesock:
	if (buf)delete[] buf;
	return m_Reader.GetLength();

data:
	return  m_Reader.GetLength();
}

int CSocketClient::CheckWrite()
{
	return m_Write.GetLength();
}

int CSocketClient::Read(uint8_t *src, size_t srcSize)
{
	const int bufLen = m_Reader.GetLength();
	const int readLen = bufLen > srcSize ? srcSize : bufLen;
	if (src == NULL)
		return m_Reader.GetLength();
	
	memcpy(src,m_Reader.GetData(),readLen);
	m_Reader.Offset(readLen);
	return readLen;
}

int CSocketClient::Write(uint8_t *src, size_t srcSize)
{
	if (m_Socket == INVALID_SOCKET)
		return -1;
	return send(m_Socket,(char*)src,srcSize,0);
}	

int CSocketClient::Close()
{
	return 0;
}
