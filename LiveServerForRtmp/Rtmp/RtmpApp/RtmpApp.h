#pragma once

#include "stdafx.h"
#include "RtmpInstance/RtmpInstance.h"

struct RtmpAppOptional{string name;string ip;int port;};

class CRtmpApp 
{
protected:
	CRtmpApp(RtmpAppOptional appOpt);
	virtual ~CRtmpApp();

	
protected:
	//rtmp url :rtmp://localhost:1935/testapp/instance1
	CRtmpInstance* Selete(const char* rtmpurl,void* searcher);
	
private:
	RtmpAppOptional m_Option;
	list<CRtmpInstance*> m_Instances;
};
