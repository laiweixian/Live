#pragma once

#include "RtmpClient.h"
#include "RtmpApp/RtmpApp.h"

typedef void* IO_HANDLE;

class IIOOperation
{
protected:
	IIOOperation() = default;
	virtual ~IIOOperation() = default;

public:
	virtual int WriteForHandle(const IO_HANDLE handle,uint8_t* buf,uint32_t length) = 0;
	virtual int CloseForHandle(const IO_HANDLE handle) = 0;
};

struct Client
{
	IO_HANDLE    handle;
	CRtmpClient *pClient;
};

class CClientManager 
{
public:
	CClientManager(uint32_t chunkSize, IIOOperation* oPera);
	~CClientManager();
public:
	int Initialize();
	int Run();

	void Enter(const IO_HANDLE handle);
	void Processing(const IO_HANDLE handle,uint8_t* buf,const uint32_t length);
	void Leave(const IO_HANDLE handle);

	int WriteToUser(CRtmpClient* pClient, uint8_t* buf, const uint32_t length);
	int CloseUser(CRtmpClient* pClient);


private:
	const uint32_t m_DefaultChunkSize;
	IIOOperation *m_Operation;
	vector<Client> m_Clients;
	CRtmpApp *m_App;
};

