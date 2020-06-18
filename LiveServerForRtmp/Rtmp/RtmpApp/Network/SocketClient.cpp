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
	byte buf[1024] = {0};

	if (m_Socket == INVALID_SOCKET)
		goto closesock;

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
			write2file(TEXT("socketclient"),buf,length);
			m_Reader.WriteIn(buf,length);
		}
		else
		{
			errorCode = WSAGetLastError();
			if (errorCode == WSAEWOULDBLOCK)
				break;
			else
			{
				closesocket(m_Socket);
				m_Socket = INVALID_SOCKET;
				goto closesock;
			}
		}
	}
	return m_Reader.GetLength();
closesock:
	return m_Reader.GetLength();
}



int CSocketClient::Read(uint8_t *src, size_t srcSize)
{
	int length = m_Reader.ReadOut(src, srcSize);
	return length;
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
