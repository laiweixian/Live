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
enum  DataType
{
	NONE,SS,WW
};
struct ObjectMember
{
	int name;
	DataType dType;

	int *dInt;
	bool *dBool;
	std::string *dStri;

};

struct t {
	int a;
	char b;
	float* c;
};


int main()
{
    return 0;
}


