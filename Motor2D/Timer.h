#ifndef __TIMER_H__
#define __TIMER_H__

#include "p2Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	void Resume();

	float ReadSec() const;
	uint32 Read() const;

private:

	bool	running;
	uint32	started_at;
	uint32	stopped_at;
};

#endif //__TIMER_H__