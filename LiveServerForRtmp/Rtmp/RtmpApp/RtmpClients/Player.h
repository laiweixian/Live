#pragma once
#include "stdafx.h"

#include "Rtmp/RtmpApp/RtmpMessage/RtmpMessage.h"

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
	virtual int PlayVideo(CVideoMessage *pMsg) final;
	virtual int PlayAudio(CAudioMessage *pMsg) final;
	virtual int PlayMsg(CBaseMessage *pMsg) final; 
	
protected:
	virtual uint32_t GetChunkSize() = 0;
	virtual int Send2Peer( uint8_t* src, const int srcLength) = 0;
protected:
	virtual int Connenct(string name) final;
	virtual int DisConnect() final;


protected:
	string     m_Name;
	IRoom4Player *m_Room;
};

