// LiveServerForRtmp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Rtmp/Rtmp.h"


int main()
{
	CRtmp rtmp;
	rtmp.PreInitialize();
	rtmp.Initialize();
	rtmp.Run();
    return 0;
}

