#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "p2Defs.h"
#include "p2Point.h"

struct SDL_Texture;

enum Faction {
	AMERICAN,
	RUSSIAN
};

class Entity
{
public:
	Entity();
	~Entity();

	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };

	void DecreaseLife(float damage);
	virtual void Die() {};

public:
	fPoint position;

protected:
	SDL_Texture* sprite;
	uint max_life;
	uint current_life;
	Faction faction;
};
#endif // _ENTITY_H_