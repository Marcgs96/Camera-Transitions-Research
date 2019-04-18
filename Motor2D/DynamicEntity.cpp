#include "CardManager.h"
#include "DynamicEntity.h"



DynamicEntity::DynamicEntity()
{
}


DynamicEntity::~DynamicEntity()
{
}


void DynamicEntity::SetCard(Card* card)
{
	entity_card = card;
	animations = card->animations;
}