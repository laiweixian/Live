// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <cstring>
using namespace std;

void SetInt(int *i)
{
	*i = 100;
}

int main()
{
	int *i = NULL;
	SetInt(i);
    return 0;
}


