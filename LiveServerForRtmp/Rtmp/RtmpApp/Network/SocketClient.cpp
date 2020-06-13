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
	m_Reader->ptr = m_Reader->buff;
	return 0;
}

int CSocketClient::InitWriteBuff()
{
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
			//对端关闭连接
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
			break;
		}
		else if (length > 0)
		{
			AppendReadBuff(buf,length);
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
				break;
			}
		}
	}

	delete[] buf;
	return GetReadBufLength();

closesock:
	return GetReadBufLength();
}

int CSocketClient::CheckWrite()
{
	return m_Writer->length;
}

int CSocketClient::Read(char *src, size_t srcSize)
{
	
	return	CopyReadBuf(src, srcSize);
}

int CSocketClient::Write(char *src, size_t srcSize)
{
	if (m_Socket == INVALID_SOCKET)
		return -1;
	return send(m_Socket,src,srcSize,0);
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
		//缓冲区扩容
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

int CSocketClient::CopyReadBuf(char *src, size_t srcSize)
{
	const int maxNum = srcSize > m_Reader->length ? m_Reader->length : srcSize;

	if (src == NULL)
		return m_Reader->length;
		

	memcpy(src, m_Reader->ptr, maxNum);
	m_Reader->ptr += maxNum;
	m_Reader->length -= maxNum;
	return maxNum;
}

