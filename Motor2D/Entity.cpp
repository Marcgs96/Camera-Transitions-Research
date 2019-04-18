#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::DecreaseLife(float damage)
{
	current_life -= damage;
	if (current_life < 0)
		current_life = 0;
}
