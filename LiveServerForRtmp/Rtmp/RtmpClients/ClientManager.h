#pragma once

#include "RtmpClient.h"

class IClientOperation
{
protected:
	IClientOperation() = default;
	virtual ~IClientOperation() = default;

public:
	virtual int WriteOperation(const void *pUser,uint8_t* buf,uint32_t length) = 0;
	virtual int CloseOperation(const void *pUser, uint8_t* buf, uint32_t length) = 0;
};

struct Client
{
	const void* pUser;
	CRtmpClient *pClient;
};

class CClientManager 
{
public:
	CClientManager(uint32_t chunkSize, IClientOperation* oPera);
	~CClientManager();
public:
	void Enter(const void* pUser);
	void Processing(const void* pUser,uint8_t* buf,const uint32_t length);
	void Leave(const void* pUser);


private:
	const uint32_t m_DefaultChunkSize;
	IClientOperation *m_Operation;
	vector<Client> m_Clients;
};
