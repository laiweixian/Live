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
	
	uint8_t* GetData();
	int GetLength(); 
	int MoveReaderPtr(int length);
private:
	void ExtendBuff();
	int  GetWritableLen();
	int GetReadLength();
private:
	uint8_t *m_Buf;
	uint32_t m_BufLen;

	uint8_t *m_WritePtr;
	uint8_t *m_ReadPtr;
};
