#include "Enemies.h"

Enemy::Enemy()
{
	//Target MUST be initialized by subclasses
	state = IDLE;
	position[0] = 0;
	position[1] = 0;
	target[0] = 0;
	target[1] = 0;
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

void movement(tGame_Element ** map, int & posX, int & posY, int targetX, int targetY, tDirection & lastDirection) {
	tDirection nextDir;
	int minimumDistance;
	switch (lastDirection) {
	case UP: { //If the last direction was UP, we only check UP, LEFT and RIGHT directions
		nextDir = UP;
		minimumDistance = 0;
		if (ALLOWED_OBJECTS.count(map[posX][posY + 1])) { 
			minimumDistance = distance(posX, posY + 1, targetX, targetY); 
			//We set as the minimum distance the one that corresponds to the direction we are in.
			nextDir = UP;
		}
		if (ALLOWED_OBJECTS.count(map[posX + 1][posY])) {
			if (minimumDistance > distance(posX + 1, posY, targetX, targetY)) {
	//Only if the distance in other direction is lower than the one that was the minimum one we set this new direction as the movement one.
				nextDir = RIGHT;
				minimumDistance = distance(posX + 1, posY, targetX, targetY);
			}
		}
		if (ALLOWED_OBJECTS.count(map[posX - 1][posY])) {
			if (minimumDistance > distance(posX - 1, posY, targetX, targetY)) {
				nextDir = LEFT;
				minimumDistance = posX - 1, posY, targetX, targetY;
			}
		}
	}
			 break;
	case DOWN: {
		nextDir = DOWN;
		minimumDistance = 0;
		if (ALLOWED_OBJECTS.count(map[posX][posY - 1])) {
			minimumDistance = distance(posX, posY - 1, targetX, targetY);
			nextDir = DOWN;
		}
		if (ALLOWED_OBJECTS.count(map[posX + 1][posY])) {
			if (minimumDistance > distance(posX + 1, posY, targetX, targetY)) {
				nextDir = RIGHT;
				minimumDistance = distance(posX + 1, posY, targetX, targetY);
			}
		}
		if (ALLOWED_OBJECTS.count(map[posX - 1][posY])) {
			if (minimumDistance > distance(posX - 1, posY, targetX, targetY)) {
				nextDir = LEFT;
				minimumDistance = posX - 1, posY, targetX, targetY;
			}
		}
	}
			   break;
	case RIGHT: {
		nextDir = RIGHT;
		minimumDistance = 0;
		if (ALLOWED_OBJECTS.count(map[posX][posY + 1])) {
			minimumDistance = distance(posX, posY + 1, targetX, targetY);
			nextDir = UP;
		}
		if (ALLOWED_OBJECTS.count(map[posX][posY - 1])) {
			if (minimumDistance > distance(posX, posY - 1, targetX, targetY)) {
				nextDir = DOWN;
				minimumDistance = distance(posX, posY - 1, targetX, targetY);
			}
		}
		if (ALLOWED_OBJECTS.count(map[posX + 1][posY])) {
			if (minimumDistance > distance(posX + 1, posY, targetX, targetY)) {
				nextDir = RIGHT;
				minimumDistance = posX + 1, posY, targetX, targetY;
			}
		}
	}
				break;
	case LEFT: {
		nextDir = LEFT;
		minimumDistance = 0;
		if (ALLOWED_OBJECTS.count(map[posX][posY + 1])) {
			minimumDistance = distance(posX, posY + 1, targetX, targetY);
			nextDir = UP;
		}
		if (ALLOWED_OBJECTS.count(map[posX][posY - 1])) {
			if (minimumDistance > distance(posX, posY - 1, targetX, targetY)) {
				nextDir = DOWN;
				minimumDistance = distance(posX, posY - 1, targetX, targetY);
			}
		}
		if (ALLOWED_OBJECTS.count(map[posX - 1][posY])) {
			if (minimumDistance > distance(posX - 1, posY, targetX, targetY)) {
				nextDir = LEFT;
				minimumDistance = posX - 1, posY, targetX, targetY;
			}
		}
	}
	}
	switch (nextDir) { //According to the new direction that we have previosuly chosen we modify the ghost given position
	case(UP) : posY = posY + 1;
		break;
	case(DOWN): posY = posY - 1;
		break;
	case(RIGHT): posX = posX + 1;
		break;
	case(LEFT): posX = posX - 1;
		}
	lastDirection = nextDir; 
	//Finally, we set as the last direction the one in which we have made the movement, in order to consider it when making another mov.
}

int distance(int posX, int posY, int targetX, int targetY) {
	int vertical = abs(posX - targetX);
	int horizontal = abs(posY - targetY);
	return vertical + horizontal;
	//This funcion simply returns the addition of the horizontal an vertical distance between coordinates of the ghost and its target.
}
