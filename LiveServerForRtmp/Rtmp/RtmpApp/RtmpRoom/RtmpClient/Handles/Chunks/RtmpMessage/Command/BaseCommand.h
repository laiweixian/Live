#pragma once

#include "stdafx.h"

namespace BaseCommand
{
	struct DataInt;
	struct DataBoolean;
	struct DataString;
	struct DataObject; 
	
	enum   DataType { NONE = 0x00, INT, BOOLEAN, STRING, OBJECT };
	typedef int64_t DataInt;
	typedef bool DataBoolean;
	typedef string DataString;

	struct ObjectMember
	{
		DataString name;
		DataType dType;
	
		DataInt *dInt;
		DataBoolean *dBool;
		DataString *dStri;
		DataObject *dObject;
	};
	
	struct DataObject
	{
		DataString name;
		ObjectMember *pMembers;
		DataInt memCount;
	};

	
}