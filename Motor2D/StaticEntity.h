#ifndef _STATIC_ENTITY_H_
#define _STATIC_ENTITY_H_

#include "Entity.h"

enum Static_State {
	IDLE,
	DIE,
	DESTROYED
};


class StaticEntity : public Entity
{
public:
	StaticEntity();
	~StaticEntity();

	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };

	virtual void Die() {};
};

#endif // _STATIC_ENTITY_H_



