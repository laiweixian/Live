#pragma once

class IPlayer
{
protected:
	IPlayer() = default;
	~IPlayer() = default;

	virtual int Leave() = 0;	
	virtual int Pause() = 0;
private:
	
};
