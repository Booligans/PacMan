#include "Enemies.h"

Enemy::Enemy()
{
	//Target MUST be initialized by subclasses
	state = IDLE;
	position[0] = 0;
	position[1] = 0;
	target[0] = 0;
	target[1] = 1;
}

void Enemy::SetState(tState s)
{
	state = s;
}

tState Enemy::GetState() const
{
	return state;
}

Enemy::~Enemy()
{
	//No pointers for now -> Empty
}

RedGhost::RedGhost(int posX, int posY, int targetX, int targetY)
{
	SetPosition(posX, posY);
	SetTarget(targetX, targetY);
}

PinkGhost::PinkGhost(int posX, int posY, int targetX, int targetY)
{
	SetPosition(posX, posY);
	SetTarget(targetX, targetY);
}

OrangeGhost::OrangeGhost(int posX, int posY, int targetX, int targetY)
{
	SetPosition(posX, posY);
	SetTarget(targetX, targetY);
}

BlueGhost::BlueGhost(int posX, int posY, int targetX, int targetY)
{
	SetPosition(posX, posY);
	SetTarget(targetX, targetY);
}
