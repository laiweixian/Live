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

int main()
{
	ObjectMember *p = new ObjectMember;
	ObjectMember *p1 = new ObjectMember{100,DataType::NONE,NULL,NULL,NULL};
	ObjectMember *p2 = new ObjectMember[100]{ {1100,DataType::NONE,NULL,NULL,NULL} };


	int i = p2[0].name;
	delete p;
	delete p1;
	delete[] p2;
    return 0;
}


