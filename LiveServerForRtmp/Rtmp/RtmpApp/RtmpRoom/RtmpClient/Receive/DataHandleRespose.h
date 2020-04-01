#pragma once

#include "stdafx.h"

enum DataHandleType
{
	INVALID, HANDSHAKE, MESSAGE
};

class IHandshakeRespose
{
protected:
	IHandshakeRespose() = default;
public:
	IHandshakeRespose() = default;

	virtual void SO(char* buff,const int buffLen) = 0;
	virtual void S1(char* buff, const int buffLen) = 0;
	virtual void S2(char* buff, const int buffLen) = 0;
};

class IMessageRespose
{
protected:
	~IMessageRespose() = default;
private:
	IMessageRespose() = default;

	virtual void SetChunkSize(uint32_t chunkSize) = 0;
	virtual void AbortMessage(uint32_t chunkStreamID) = 0;
	virtual void Acknowledgement(uint32_t sequenceNumber) = 0;
	virtual void WindowAcknowledgementSize(uint32_t acknowledgeWindowSize) = 0;
	virtual void SetPeerBandwidth(uint32_t acknowledgeWindowSize , uint8_t limitType) = 0;
	virtual void UserControlMessages() = 0;		//参数待定
	virtual void CommandMessage() =	0;			//参数待定
	virtual void DataMessage() = 0;				//参数待定
	virtual void SharedObjectMessage() = 0;		//参数待定
	virtual void AudioMessage(char* buff, const int buffLen) = 0;
	virtual void VideoMessage(char* buff,const int buffLen) = 0;
	virtual void AggregateMessage() = 0;		//参数待定
};

class IDataHandleRespose : public IHandshakeRespose , public IMessageRespose
{
protected:
	~IDataHandleRespose() = default;
public:
	IDataHandleRespose() = default;
};

