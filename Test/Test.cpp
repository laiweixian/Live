// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	string sInt("2ppp");
	string sFloat("12.2");
	
	
	int v;
	try
	{
		v = std::stoi(sInt);
	}
	catch (const std::exception& e)
	{
		const char *msg = e.what();

	}
	
    return 0;
}

