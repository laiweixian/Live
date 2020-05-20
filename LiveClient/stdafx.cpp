
// stdafx.cpp : 只包括标准包含文件的源文件
// LiveClient.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


void PrintError(const char * format, ...)
{
	return ;
}

void PrintLog(const char * format, ...)
{
	return ;
}


void LogCallBack(void *avcl,int level,const char * 	fmt,va_list vl)
{
	FILE *fp ;
	fopen_s(&fp,"my_log.txt", "a+");
	if (fp) {
		vfprintf(fp, fmt, vl);
		fflush(fp);
		fclose(fp);
	}


}

int InitFFMpeg()
{
	av_log_set_callback(LogCallBack);	
	return 0;
}