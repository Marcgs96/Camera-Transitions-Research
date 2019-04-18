#ifndef _SUMMONER_H_
#define _SUMMONER_H_

#include "Entity.h"

class Deck;

class Summoner : public Entity
{
public:
	Summoner();
	~Summoner();
	bool CleanUp() { return true; }
	Deck* deck;

private:
	uint max_energy;
	uint current_energy;
	uint energy_regen;
};

#endif // !_SUMMONER_H_


