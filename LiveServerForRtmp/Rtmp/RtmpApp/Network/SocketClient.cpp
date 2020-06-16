#include "SocketClient.h"
#include "stdafx.h"
#define BUFF_LEN	1024

CSocketClient::CSocketClient(SOCKET so,sockaddr_in addr):m_Socket(so), m_Addr(addr)
{
	InitReadBuff();
	InitWriteBuff();
}

CSocketClient::~CSocketClient()
{
	TRACE("addr:%s close\n ", inet_ntoa(m_Addr.sin_addr));
	closesocket(m_Socket);
}

int CSocketClient::InitReadBuff()
{
	m_Reader = new ClientBuffer;
	m_Reader->totalLen = BUFF_LEN;
	m_Reader->buff = new uint8_t[BUFF_LEN];
	memset(m_Reader->buff,0,BUFF_LEN);
	
	m_Reader->length = 0;
	m_Reader->ptr = m_Reader->buff;
	return 0;
}

int CSocketClient::InitWriteBuff()
{
	m_Writer = new ClientBuffer;
	m_Writer->totalLen = BUFF_LEN;
	m_Writer->buff = new uint8_t[BUFF_LEN];
	memset(m_Writer->buff, 0, BUFF_LEN);
	
	m_Writer->length = 0;
	m_Writer->ptr = m_Writer->buff;
	return 0;
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
			//�Զ˹ر�����
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
			goto closesock;
		}
		else if (length > 0 )
		{
			AppendReadBuff(buf,length);
			if (length < 1024)
				goto data;
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
	return GetReadBufLength();

data:
	length = GetReadBufLength();
	return length;
}

int CSocketClient::CheckWrite()
{
	return m_Writer->length;
}

int CSocketClient::Read(uint8_t *src, size_t srcSize)
{
	if (src == NULL)
		return GetReadBufLength();
	return	CopyReadBuf(src, srcSize);
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

int CSocketClient::AppendReadBuff(byte* src, int length)
{
	const int newlen = length + m_Reader->length;
	const int leftLen = m_Reader->totalLen - m_Reader->length;

	if (newlen > m_Reader->totalLen)
	{
		//����������
		ExtendReadBuf();
		return AppendReadBuff(src, length);
	}
	else
	{
		if (leftLen < length)
			CleanReadBuf(); 
		m_Reader->length += length;
		memcpy(m_Reader->ptr,src,length);
	}

	return m_Reader->length;
}

int CSocketClient::ExtendReadBuf()
{
	byte *temp = NULL;
	temp = new byte[m_Reader->length];
	memcpy(temp, m_Reader->ptr, m_Reader->length);

	delete[] m_Reader->buff;
	m_Reader->buff = NULL;

	m_Reader->totalLen += BUFF_LEN;
	m_Reader->buff = new uint8_t[m_Reader->totalLen];
	memset(m_Reader->buff, 0, m_Reader->totalLen);
	m_Reader->ptr = m_Reader->buff;

	memcpy(m_Reader->buff, temp, m_Reader->length);
	delete[] temp;
	temp = NULL;

	return 0;
}

int CSocketClient::CleanReadBuf()
{
	byte *temp = NULL;
	temp = new byte[m_Reader->length];
	memcpy(temp, m_Reader->ptr, m_Reader->length);

	memset(m_Reader->buff,0,m_Reader->totalLen);
	memcpy(m_Reader->buff,temp,m_Reader->length);

	m_Reader->ptr = m_Reader->buff;

	return 0;
}

int CSocketClient::GetReadBufLength()
{
	return m_Reader->length;
}

int CSocketClient::CopyReadBuf(uint8_t *src, size_t srcSize)
{
	const int maxNum = srcSize > m_Reader->length ? m_Reader->length : srcSize;

	if (src == NULL)
		return m_Reader->length;
		

	memcpy(src, m_Reader->ptr, maxNum);
	m_Reader->ptr += maxNum;
	m_Reader->length -= maxNum;
	return maxNum;
}

