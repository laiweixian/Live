// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <WinSock2.h>
#include <stdint.h>
#include "Rtmp/Util/RtmpUtils.h"
using namespace std;
#pragma comment(lib, "wininet.lib")

// TODO:  在此处引用程序需要的其他头文件

static int write2file(LPCSTR name,uint8_t *src, const int srcLen)
{
	if (src == NULL || srcLen == 0)
		return 0;

	const char* path = "C:\\Users\\Administrator\\source\\repos\\laiweixian\\Live\\Debug\\";
	string file;

	file.append(path);
	file.append(name);

	HANDLE hFILE = CreateFile(file.data(),GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFILE == INVALID_HANDLE_VALUE)
	{
		hFILE = CreateFile(file.data(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFILE == INVALID_HANDLE_VALUE)
			return 0;
	}

	SetFilePointer(hFILE,NULL,NULL, FILE_END);

	DWORD dwWrite;
	WriteFile(hFILE, src, srcLen, &dwWrite, NULL);

	FlushFileBuffers(hFILE);

	CloseHandle(hFILE);
	return 0;
}

static void TRACE(const char* strLogStr, ...)
{
	va_list args;
	va_start(args, strLogStr);
	vprintf(strLogStr, args);
	va_end(args);

	//
	write2file("log.txt", (uint8_t*) const_cast<char*>(strLogStr), strlen(strLogStr)+1);
}
