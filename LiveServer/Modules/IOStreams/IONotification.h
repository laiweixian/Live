#pragma once

#include "stdafx.h"

class CIONotification
{
protected:
	~CIONotification() {}
	CIONotification() {}

public:
	virtual const char* GetIOStreamName() = 0;
	virtual const char* GetEventName() = 0;
	virtual int OnOpen(const int ioID) = 0;
	virtual int OnReceive(const int ioID) = 0;
	virtual int OnSend(const int ioID) = 0;
	virtual int OnClose(const int ioID) = 0;
};
static vector<CIONotification*> G_IONotifications;
static ULONG register_io_notification(CIONotification* pNotifi)
{
	auto it = G_IONotifications.begin();
	CIONotification* tempIO = NULL;

	for (it = G_IONotifications.begin(); it != G_IONotifications.end(); it++)
	{
		tempIO = (*it);
		if (pNotifi == tempIO)
			return SAR_ERR;
	}
	G_IONotifications.push_back(pNotifi);
	return SAR_OK;
}

static ULONG release_all_notification()
{

}
