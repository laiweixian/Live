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
	int Connect(const char* rtmpurl,void* searcher);
	int DisConnect(const char* rtmpurl, void* searcher);
	int PublishMedia(const char* rtmpurl, void* searcher);
	int PlayMedia(const char* rtmpurl, void* searcher);
	
private:
	RtmpAppOptional m_Option;
	list<CRtmpInstance*> m_Instances;
};
