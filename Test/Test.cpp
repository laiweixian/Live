// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <cstring>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
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

void parse_valist_by_flag(t *pt, ...)
{
	va_list p_args;
	int idx = 0;
	int a = 0;
	int count = 0;

	va_start(p_args, pt);
	t *var = NULL;
	while ((var = va_arg(p_args, t*)) != NULL) {
		idx++;
	}
	va_end(p_args);
	printf("����:%d\n", idx);

	va_start(p_args, pt);
	while ((var = va_arg(p_args, t*)) != NULL) {
		count++;
	}
	va_end(p_args);
	printf("����:%d\n", count);
}



int main()
{
	uint8_t a = 0x03;
	uint8_t b = a << 1;
    return 0;
}


