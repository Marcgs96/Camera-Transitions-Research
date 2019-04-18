#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include "Timer.h"
#include "p2Point.h"
#include "SDL\include\SDL_rect.h"
#include "Color.h"

class Transition
{
private:
	enum class TransitionState {
		NONE,
		ENTERING,
		ACTION,
		EXITING
	};

protected:
	TransitionState state;

	float transition_time;
	Timer* current_time = nullptr;


public:

	Transition(float transition_time);
	~Transition();

	void PostUpdate();

	//-----Update process-------

	virtual void Entering();
	virtual void Action();
	virtual void Exiting();

	float LerpValue(float percent, float start, float end);
	iPoint Lerp(float percent, iPoint origin, iPoint destination);

	//---Specific transitions methods-------
};

#endif // _TRANSITION_H_