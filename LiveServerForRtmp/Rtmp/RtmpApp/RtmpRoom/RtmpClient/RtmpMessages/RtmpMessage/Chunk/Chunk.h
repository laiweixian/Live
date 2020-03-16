#pragma once

#include "stdafx.h"

enum BasicHeaderType{INVALID,BASE0,BASE1,BASE2};
enum MessageHeaderType{ INVALID, MSG0,MSG1,MSG2,MSG3};
enum ExtendedTimestampType{ INVALID, EXT0,EXT1};

enum ChunkHeaderFieldType
{
	FMT,CSID,
	TIMESTAMP,TIMESTAMP_DELTA,MESSAGE_LENGTH,MESSAGE_TYPE_ID,MESSAGE_STREAM_ID,
	EXTENDED_TIMESTAMP
};

struct ChunkHeaderInfo
{
	uint8_t fmt;
	uint32_t csid;
	uint32_t timestamp;
	uint32_t timestamp_delta;
	uint32_t message_length;
	uint8_t message_type_id;
	uint32_t message_stream_id;
	uint32_t extended_timestamp;
};



class CChunk
{
private:
	CChunk();
	~CChunk();

public:
	
	static CChunk* DeMultiplexing(char* buff,const int buffLen,int* outChunkLen);
	void Destory() ;
	
	int GetHeaderLength();
	BasicHeaderType GetBaseHeaderType();
	MessageHeaderType GetMessageHeaderType();
	ExtendedTimestampType GetExtendedTimestampType();

	ChunkHeaderInfo GetInfo();
private:
	void Restore();
	
	int Demux(char* buff, const int buffLen, int* outChunkLen);
	//chunk header
	int DemuxChunkHeader(char* buff, const int buffLen, int* outChunkHeaderLen);
	int DemuxBaseHeader(char* buff, const int buffLen, int* outBasicLen);
	int DemuxMsgHeader(char* buff, const int buffLen, int* outMsgLen);
	int DemuxExtendedTimestamp(char* buff, const int buffLen, int* outExtLen);

	void SetFMT(void *buff,const int buffLen = 1);
	void SetCSID(void *buff, const int buffLen);
	void SetTimestamp(void *buff, const int buffLen = 3);
	void SetTimestampDelta(void *buff, const int buffLen = 3);
	void SetMessageLength(void *buff, const int buffLen = 3);
	void SetMessageTypeID(void *buff, const int buffLen = 1);
	void SetMessageStreamID(void *buff, const int buffLen = 4);
	void SetExtendedTimestamp(void *buff, const int buffLen );
private:
	static int GetByteLength(BasicHeaderType baseType);
	static int GetByteLength(MessageHeaderType msgType);
	static int GetByteLength(ExtendedTimestampType extType);


private:


	BasicHeaderType m_BasicHeader;
	MessageHeaderType m_MsgHeader;
	ExtendedTimestampType m_ExT;
	int m_ChunkDataLen;

	CChunk *m_Prev;
	int		m_ChunkSize;

	vector<ChunkHeaderFieldType> m_FieldTypes;
	ChunkHeaderInfo m_Info;
};
