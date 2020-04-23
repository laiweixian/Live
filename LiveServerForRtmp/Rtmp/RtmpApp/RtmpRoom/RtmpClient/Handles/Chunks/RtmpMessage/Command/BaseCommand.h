#pragma once

#include "stdafx.h"

namespace BaseCommand
{
	struct DataInt;
	struct DataBoolean;
	struct DataString;
	struct DataObject; 
	union DataVariable;
	
	
	enum   DataType { NONE = 0x00, INT, BOOLEAN, STRING, OBJECT };
	typedef int64_t DataInt;
	typedef bool DataBoolean;
	typedef string DataString;

	union DataVariable
	{
		DataInt dInt;
		DataBoolean dBool;
		DataString dStri;
		DataObject *ptrObject;
	};
	struct ObjectMember
	{
		DataString name;
		DataType dType;
		DataVariable dVariable;
	};
	
	struct DataObject
	{
		DataString name;
		ObjectMember *pMembers;
		DataInt memCount;
	};
}