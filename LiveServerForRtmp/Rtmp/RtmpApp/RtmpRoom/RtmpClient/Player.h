#pragma once
#include "stdafx.h"

#define PLAYER_OK		0
#define PLAYER_FAILURE	1
#define ERR_NO_ROOM		-1

class IRoom4Player;

class CPlayer
{
protected:
	CPlayer() ;
	virtual ~CPlayer() ;

public:
	virtual int OffLineEvent() = 0;

	
private:
	virtual int Run(string name) ;	//enter room
	virtual int Pause() ;	//pause request all data
	virtual int Stop()  ;	//leave room
protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer(const uint8_t* src, const int srcLength) = 0;
protected:
	virtual int ConnectRoom(string name) final;
	virtual int DisConnectRoom() final;

	virtual bool GetActive()  final;
	virtual string GetName() final;
protected:
	string     m_Name;
	IRoom4Player *m_Room;
};

