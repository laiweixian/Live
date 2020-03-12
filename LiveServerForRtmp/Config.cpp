#include "Config.h"

CConfig::CConfig(const char* config)
{
	int len;

	len = strlen(config);
	m_ConfigSize = len + 1;
	m_Config = new char[m_ConfigSize];
	memset(m_Config, 0, m_ConfigSize);

	strcpy(m_Config, config);
	m_ItemObjects.clear();
}

CConfig::~CConfig()
{
	auto it = m_ItemObjects.begin();
	
}

int CConfig::RegisterItem(const char* parent, const char* itemName, ItemType itemType, const int itemLen, void* dst, int *outSize)
{
	//
	auto it = m_ItemObjects.begin();
	char *ptr = NULL,*start = NULL, *end = NULL,*rowStart = NULL , *rowEnd = NULL;
	const char *leftBracket = "{", *rightBracket = "}",*CRLF = "\r\n";
	int leftBracketCount = 0, rightBracketCount = 0;
	bool noParent = true;
	string parentObject,item ,itemKey, itemValue;
	string::size_type posStart,posEnd,posEqual;
	ItemObject *pObject = NULL, *pTempItem = NULL;
	void *value = NULL;
	int valueSize  = 0;

	if (m_Config == NULL)
		return;
	
	for (it = m_ItemObjects.begin(); it != m_ItemObjects.end(); it++)
	{
		pTempItem = *it;
		if (!(pTempItem->iKey).compare(itemName))
			return 0;
	}

	//search item 
	if (parent != NULL)
	{
		start = strstr(m_Config, parent);
		if (ptr == NULL)
			return NO_PARENT_ERROR;

		ptr =  strstr(start, leftBracket);
		while (ptr && (ptr != m_Config + strlen(m_Config)))
		{
			if (*ptr == *leftBracket)
				leftBracketCount++;
			else if (*ptr == *rightBracket)
				rightBracketCount++;
				
			if (leftBracketCount == rightBracketCount && leftBracketCount != 0)
			{
				noParent = false;
				break;
			}
			ptr++;
		}

		if (noParent)
			return NO_PARENT_ERROR;
		end = ptr;
	}
	else
	{
		start = m_Config;
		end = m_Config + strlen(m_Config);
	}

	parentObject.copy(start, end - start);
	posStart = parentObject.find(itemName);
	if (posStart == parentObject.npos)
		return NO_ITEM_ERROR;
	posEnd = parentObject.find(CRLF, posStart);
	if (posStart == parentObject.npos)
		return NO_ITEM_ERROR;

	item = parentObject.substr(posStart, posEnd-posStart);
	CConfig::Trim(item);
	
	posEqual = item.find('=');
	if (posEqual == item.npos)
		return NO_ITEM_EQUAL_ERROR;

	itemKey = item.substr(0, posEqual);
	itemValue = item.substr(posEqual, item.npos);

	pObject = new ItemObject;
	pObject->iType = itemType;
	pObject->iKey = itemKey;
	pObject->iValue = itemValue;
	m_ItemObjects.push_back(pObject);

	switch (itemType)
	{
	case STRING_TYPE:
		valueSize = pObject->iValue.length();
		value = new char[valueSize];
		memcpy(value,pObject->iValue.c_str(), valueSize);
		break;
	case INT_TYPE:
		valueSize = sizeof(int);
		value = new int;
		


		break;
	case DOUBLE_TYPE:
		break;
	case BOOL_TYPE:
		break;
	case ARRAY_TYPE:
		break;
	case ITEM_INVALID:
		break;
	default:
		break;
	}

	return 0;
}

void CConfig::Trim(string& s)
{
	int index = 0;
	if (!s.empty())
	{
		while ((index = s.find(' ', index)) != string::npos)
			s.erase(index, 1);
	}
}