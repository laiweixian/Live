#pragma once

#include "RtmpClient.h"

class IOperation
{
protected:
	IOperation() = default;
	virtual ~IOperation() = default;

public:
	virtual int WriteOperation() = 0;
	virtual int ReadOperation() = 0;
	virtual int CloseOperation() = 0;
};

class CClientManager 
{
public:
	CClientManager(uint32_t chunkSize);
	~CClientManager();
public:
	int Enter(void *pUser);
	int Processing(void* pUser,uint8_t* buf,uint32_t bufLength);
	int Leave(void *pUser);


private:
	uint32_t m_ChunkSize;
	vector<CRtmpClient*> m_Clients;
};
