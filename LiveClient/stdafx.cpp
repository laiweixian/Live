
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// LiveClient.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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