#include "Buffer.h"

CBuffer::CBuffer(const int len) :m_Base(len),m_Buff(NULL),m_BuffSize(0),m_Ptr(NULL),m_Length(0)
{	
	m_BuffSize = m_Base;
	m_Buff = new uint8_t[m_BuffSize];

	m_Ptr = m_Buff;
	m_Length = 0;
}

CBuffer::~CBuffer()
{
	delete[] m_Buff;
	m_Buff = NULL;
	m_Ptr = NULL;
	m_BuffSize = 0;
	m_Length = 0;
}

int CBuffer::Append(uint8_t* src, int len)
{
	const int newlen = len + m_Length;
	const int leftLen = m_BuffSize - m_Length;

	if (newlen > m_BuffSize)
	{
		//»º³åÇøÀ©ÈÝ
		ExtendBuff();
		return Append(src, len);
	}
	else
	{
		if (leftLen < len)
			CleanBuff();
		memcpy(m_Ptr, src, len);
		m_Length += len;
	}

	return GetLength();
}

int CBuffer::Seek(int len)
{
	if (m_Length >= len)
	{
		m_Ptr += len;
		m_Length -= len;
	}
	else 
		return -1;

	return 0;
}

void CBuffer::ExtendBuff()
{
	uint8_t *temp = NULL;
	int length = m_Length;
	temp = new uint8_t[length];
	memcpy(temp, m_Ptr, length);

	delete[] m_Buff;
	m_BuffSize += m_Base;
	m_Buff = new uint8_t[m_BuffSize];
	memset(m_Buff,0,m_BuffSize);
	m_Ptr = m_Buff;	

	memcpy(m_Ptr,temp,length);
	m_Length = length;

	delete[] temp; temp = NULL;
}

int CBuffer::GetLength()
{
	return m_Length;
}
uint8_t* CBuffer::GetData()
{
	return m_Ptr;
}

void CBuffer::CleanBuff()
{
	uint8_t *temp = NULL;
	int length = m_Length;
	temp = new uint8_t[length];
	memcpy(temp, m_Ptr, length);

	memset(m_Buff,0,m_BuffSize);

	memcpy(m_Buff,temp,length);

	m_Ptr = m_Buff;
	m_Length = length;

	delete[] temp ; temp = NULL;
}