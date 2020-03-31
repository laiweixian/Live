#pragma once

#include "stdafx.h"

struct AMF3Data
{

};

class CAMF3
{
private:
	CAMF3();
	~CAMF3();

public:
	static CAMF3* CreateAMF3( uint8_t *pData, const int dataLen);
	void Destroy();
private:
	int Splite(uint8_t *pData, const int dataLen);
	int SpliteBasicType(uint8_t *pData, const int dataLen);
	int SpliteCompositType(uint8_t *pData, const int dataLen);
public:
	vector<AMF3Data*> m_Datas;
};