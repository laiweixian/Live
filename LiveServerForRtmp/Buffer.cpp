#include "Buffer.h"
#include "stdafx.h"

CBuffer::CBuffer():m_Buf(NULL),m_WritePtr(NULL),m_ReadPtr(NULL),m_BufLen(0)
{	
	m_BufLen = DEFAULT_SIZE;
	m_Buf = new uint8_t[m_BufLen];
	memset(m_Buf,0,m_BufLen);

	m_WritePtr = m_Buf;
	m_ReadPtr = m_WritePtr;
}

CBuffer::~CBuffer()
{
	if (m_Buf) delete[] m_Buf;	m_Buf = NULL;
	m_WritePtr = NULL;
	m_ReadPtr = NULL;
}

int CBuffer::WriteIn(uint8_t *src, uint32_t length)
{
	const int leftLen = GetWritableLen();
	if (leftLen < length)
	{
		ExtendBuff();
		return WriteIn(src,length);
	}

	memcpy(m_WritePtr,src,length);
	m_WritePtr += length;
}

int CBuffer::ReadOut(uint8_t *dst, uint32_t length)
{
	const int readLength = GetReadLength();
	int maxLen = 0;

	if (dst == NULL || length == 0)
		return readLength;

	maxLen = readLength > length ? length : readLength;
	memcpy(dst,m_ReadPtr,maxLen);
	m_ReadPtr += maxLen;
	return maxLen;
}

int CBuffer::GetReadLength()
{
	return (m_WritePtr - m_ReadPtr);
}

int  CBuffer::GetWritableLen()
{
	return ((m_Buf+m_BufLen) - m_WritePtr);
}

uint8_t* CBuffer::GetData()
{
	return m_Buf;
}
int CBuffer::GetLength()
{
	return GetReadLength();
}

int CBuffer::Seek(int length)
{
	const int readLen = GetReadLength();
	if (length > readLen)
		return -1;

	m_ReadPtr += length;
	return 0;
}


void CBuffer::ExtendBuff()
{
	const int readLength = GetReadLength();
	uint8_t *temp = NULL;

	temp = new uint8_t[readLength];	
	memcpy(temp,m_ReadPtr,readLength);

	delete[] m_Buf;

	m_BufLen += DEFAULT_SIZE;
	m_Buf = new uint8_t[m_BufLen];
	memset(m_Buf,0,m_BufLen);

	memcpy(m_Buf,temp,readLength);
	
	m_WritePtr = m_Buf + readLength;
	m_ReadPtr = m_Buf;

	delete[] temp;
	temp = NULL;
}


