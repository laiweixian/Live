#pragma once
#include <stdint.h>
#include <string.h>

#define  DEFAULT_SIZE	2048

class CBuffer
{
public:
	CBuffer();
	~CBuffer();

	int WriteIn(uint8_t *src,uint32_t length);
	int ReadOut(uint8_t *dst,uint32_t length);
	int GetReadableLen();

private:
	void ExtendBuff();
	void CleanBuff();
	int  GetWritableLen();
private:
	uint8_t *m_Buf;
	uint32_t m_BufLen;

	uint8_t *m_WritePtr;
	uint8_t *m_ReadPtr;
};
