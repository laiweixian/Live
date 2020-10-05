#pragma once

#include "stdafx.h"

class IMediaEvent
{
protected:
	IMediaEvent() = default;
	virtual ~IMediaEvent() = default;
public:
	virtual void OnSound(AVFrame* pcm) = 0;
	virtual void OnImage(AVFrame* bgr24) = 0;
};
