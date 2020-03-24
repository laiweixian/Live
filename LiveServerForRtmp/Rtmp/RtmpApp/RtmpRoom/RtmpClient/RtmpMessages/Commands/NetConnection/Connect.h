#pragma once

#include "../../AMF/AMF0.h"
#include "../../AMF/AMF3.h"
#include "stdafx.h"

struct connectCommandObject
{
	string app;
	string flashver;
	string swfUrl;
	string tcUrl;
	bool fpad;
	uint32_t audioCodecs;
	uint32_t videoCodecs;
	uint32_t videoFunction;
	string pageUrl;
	uint32_t objectEncoding;
};

struct connectOptionalUserArguments
{

};

struct connectCommand
{
	string name;
	uint64_t transactionID;

};

class CConnect
{

};
