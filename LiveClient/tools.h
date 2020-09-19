#pragma once

#include "stdafx.h"

AVFrame* YUV2BMP(AVFrame *yuv);
AVFrame* BMP2YUV(AVFrame *bgr);
int  RenderToDC(HDC hdc,AVFrame* bgr);