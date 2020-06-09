#pragma once

#include "stdafx.h"

#include "Handles/Chunks/RtmpMessage/RtmpMessage.h"

#define PUBLISHER_OK	0
#define PUBLISHER_FAILURE 1


class CPlayer;
class IRoom4Publish;

class CPublisher
{
protected:
	CPublisher();
	virtual ~CPublisher();

public:
	virtual int OnEnter(CPlayer* pPlayer) final;
	virtual int OnLeave(CPlayer* pPlayer) final;

protected:
	virtual int Run(string name) final;
	virtual int Pause() final;
	virtual int Stop()  final;

protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(const uint8_t* src, const int srcLength) = 0;
protected:
	virtual bool GetActive()  final;
	virtual string GetName() final;
	
	
private:
	bool   m_Active;
	string m_Name;
	IRoom4Publish *m_Room;
};

