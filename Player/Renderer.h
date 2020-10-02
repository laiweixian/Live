#pragma once
#include "stdafx.h"

class CRenderer
{
protected:
	CRenderer();
	virtual ~CRenderer();

protected:
	virtual HDC& GetRendererTarget(int* outLeft,int* outRight, int* outBottom ,int *outTop) = 0;

protected:
	void Renderer(AVFrame* rgb24);
};
