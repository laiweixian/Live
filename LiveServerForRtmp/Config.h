#pragma once

#include "stdafx.h"

enum ItemType
{
	STRING_TYPE,INT_TYPE,DOUBLE_TYPE,BOOL_TYPE,ARRAY_TYPE,ITEM_INVALID
};

struct ItemObject
{
	ItemType iType;
	string iKey;
	string iValue;
};

#define NO_SOURCE_ERROR	(-1)
#define NO_PARENT_ERROR	(-2)
#define NO_ITEM_ERROR	(-3)
#define NO_ITEM_EQUAL_ERROR	(-4)


class CConfig
{
private:
	~CConfig();
public:
	CConfig(const char* config); 

	int RegisterItem(const char* parent,const char* itemName, ItemType itemType,const int itemLen ,void* dst,int *outSize);
	static void Trim(string& s);
private:
	vector<ItemObject*> m_ItemObjects;
	char *m_Config;
	int	  m_ConfigSize;
};