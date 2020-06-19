// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <stdint.h>

static uint8_t* ReadConnect(int *outSize)
{
	HANDLE hFile = CreateFile(TEXT("C:\\Users\\Administrator\\source\\repos\\laiweixian\\Live\\Debug\\connect"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile error.\n");
		return NULL;
	}

	int file_size = 0;
	file_size = GetFileSize(hFile, NULL);
	uint8_t *buff;
	buff = new uint8_t[file_size];
	DWORD dwRead;
	if (!ReadFile(hFile, buff, file_size, &dwRead, NULL))
	{
		printf("ReadFile error.\n");
		return NULL;
	}


	CloseHandle(hFile);
	*outSize = file_size;
	return buff;
}


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
