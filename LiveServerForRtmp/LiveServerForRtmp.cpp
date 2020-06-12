// LiveServerForRtmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Rtmp/Rtmp.h"


int main()
{
	CRtmp rtmp;
	rtmp.PreInit();
	rtmp.Init();
	rtmp.Run();
    return 0;
}

