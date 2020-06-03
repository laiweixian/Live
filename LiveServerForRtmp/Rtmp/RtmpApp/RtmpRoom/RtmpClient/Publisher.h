#pragma once

class IPublishNotification
{
protected:
	IPublishNotification() = default;
	~IPublishNotification() = default;

	virtual int OnEnter() = 0;
	virtual int OnLeave() = 0;
};

class CPublisher : public IPublishNotification
{
protected:
	CPublisher() = default;
	~CPublisher() = default;


	
};