#pragma once
#include <stdint.h>
#include <string.h>

#define  DEFAULT_SIZE	2048

class CBuffer
{
public:
	CBuffer(const int len = DEFAULT_SIZE);
	~CBuffer();

	int Append(uint8_t* src,int len);
	int GetLength();
	uint8_t* GetData();
	int Offset(int len);
private:
	void ExtendBuff();
	void CleanBuff();
private:
	uint8_t *m_Buff;
	uint64_t m_BuffSize;

	uint8_t *m_Ptr;
	uint32_t m_Length;

	uint64_t m_Base;
};
