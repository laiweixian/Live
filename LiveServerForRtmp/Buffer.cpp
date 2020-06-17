#include "Buffer.h"

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
	const int len = GetWritableLen();
	




}

int CBuffer::ReadOut(uint8_t *dst, uint32_t length)
{

}

int CBuffer::GetReadableLen()
{
	return (m_WritePtr - m_ReadPtr);
}

int  CBuffer::GetWritableLen()
{
	return (m_Buf+m_BufLen - m_WritePtr);
}


void CBuffer::ExtendBuff()
{
	const int readLen = GetReadableLen();
	uint8_t *temp = NULL;

	temp = new uint8_t[readLen];
	memcpy(temp,m_ReadPtr,readLen);

	delete[] m_Buf;	m_Buf = NULL;

	m_BufLen += DEFAULT_SIZE;
	m_Buf = new uint8_t[m_BufLen];
	memset(m_Buf,0,m_BufLen);

	memcpy(m_Buf,temp,readLen);
	m_WritePtr = m_Buf + readLen;
	m_ReadPtr = m_Buf;

	delete[] temp; temp = NULL;

}


void CBuffer::CleanBuff()
{
	uint8_t *temp = NULL;
	const int length = m_Length;

	temp = new uint8_t[length];
	memcpy(temp, m_Ptr, length);

	memset(m_Buff,0,m_BuffSize);
	memcpy(m_Buff,temp,length);

	m_Ptr = m_Buff;
	m_Length = length;

	delete[] temp ; temp = NULL;
}