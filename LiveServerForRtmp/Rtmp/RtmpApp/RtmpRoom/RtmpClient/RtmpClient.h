#pragma once



class CRtmpClient 
{
public:
	CRtmpClient();
	~CRtmpClient();

	int OnData(const char* buff,const int buffLen);

private:
	
};
