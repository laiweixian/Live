#pragma once

#include "stdafx.h"

namespace AMF3{

	class CParse;
};

class AMF3::CParse
{
private:
	CParse();
	~CParse();
public:
	static CParse* Create(uint8_t *src, const int srcLen);
	void Destroy();
};