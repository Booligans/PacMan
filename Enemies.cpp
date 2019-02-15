#include "Enemies.h"
#include <cmath>
#include <iostream>
//Enemies. Properties and functions in common.

Enemy::Enemy(tGhost ghost_type, Level const& level) {
	state = IDLE;
	idle_time = rand() % 6;
	target[0] = 0;
	target[1] = 0;
	direction = LEFT;
	animationState = 1;
	SetMaxCounter(8);
	SetCounter(GetMaxCounter());
	SetStateCounter(0);
	loadSprite(scared_sprite, "Scared-Ghost.png", 2, 1);
	loadSprite(eaten_sprite, "Ghost_Eyes.png", 2, 1);

	switch (ghost_type) {
	case RED: {
		type = RED;
		loadSprite(sprite, "Red-Ghost.png", 2, 1);
		ScatterTarget[0] = level.GetSize(0) - 1;
		ScatterTarget[1] = 0;
		SetPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetNextPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetInitialPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
	}break;
	case PINK: {
		type = PINK;
		loadSprite(sprite, "Pink-Ghost.png", 2, 1);
		ScatterTarget[0] = 0;
		ScatterTarget[1] = 0;
		SetPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetNextPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetInitialPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
	}break;
	case BLUE: {
		type = BLUE;
		loadSprite(sprite, "Blue-Ghost.png", 2, 1);
		ScatterTarget[0] = level.GetSize(level.GetSize() - 1) - 1;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetNextPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetInitialPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
	}break;
	case ORANGE: {
		type = ORANGE;
		loadSprite(sprite, "Orange-Ghost.png", 2, 1);
		ScatterTarget[0] = 0;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetNextPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetInitialPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
	}break;
	}
	//GHOST HOUSE TARGET
	if (level.GetHouseXPos() == 0 && level.GetHouseYPos() == 0) {
		initial_house.x = initial_position.x;
		initial_house.y = initial_position.y;
	}
	else {
		initial_house.x = level.GetHouseXPos();
		initial_house.y = level.GetHouseYPos();
	}
	//IDLE TARGET
	if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
		IdleTarget[0] = position.x + 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
		IdleTarget[0] = position.x - 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y - 1;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y + 1;
	}
	else {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y;
	}
	SetPixelPosition(level.GetPixelPositionX(GetPositionX()), level.GetPixelPositionY(GetPositionY()));
}

void Enemy::UpdatePositions(Level const&level) {
	switch (type) {
	case RED: 
	{
		ScatterTarget[0] = level.GetSize(0) - 1;
		ScatterTarget[1] = 0;
		SetPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetNextPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetInitialPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
	} break;
	case BLUE: 
	{
		ScatterTarget[0] = level.GetSize(level.GetSize() - 1) - 1;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetNextPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetInitialPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
	} break;
	case ORANGE:
	{
		ScatterTarget[0] = 0;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetNextPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetInitialPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
	} break;
	case PINK:
	{
		ScatterTarget[0] = 0;
		ScatterTarget[1] = 0;
		SetPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetNextPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetInitialPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
	} break;

	}

	//GHOST HOUSE TARGET
	if (level.GetHouseXPos() == 0 && level.GetHouseYPos() == 0) {
		initial_house.x = initial_position.x;
		initial_house.y = initial_position.y;
	}
	else {
		initial_house.x = level.GetHouseXPos();
		initial_house.y = level.GetHouseYPos();
	}
	//IDLE TARGET
	if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
		IdleTarget[0] = position.x + 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
		IdleTarget[0] = position.x - 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y - 1;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y + 1;
	}
	else {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y;
	}
	SetPixelPosition(level.GetPixelPositionX(GetPositionX()), level.GetPixelPositionY(GetPositionY()));
}

void Enemy::Reset(Level &level) {
	state = IDLE;
	idle_time = rand() % 6;
	direction = LEFT;
	animationState = 1;
	SetMaxCounter(8);
	SetCounter(GetMaxCounter());
	SetStateCounter(0);

	SetPosition(GetInitialPositionX(), GetInitialPositionY());
	SetNextPosition(GetInitialPositionX(), GetInitialPositionY());
	SetPixelPosition(level.GetPixelPositionX(GetInitialPositionX()), level.GetPixelPositionY(GetInitialPositionY()));
}

void Enemy::GameReset(tGhost ghost_type, Level &level) {
	state = IDLE;
	idle_time = rand() % 6;
	target[0] = 0;
	target[1] = 0;
	direction = LEFT;
	animationState = 1;
	SetMaxCounter(8);
	SetCounter(GetMaxCounter());
	SetStateCounter(0);

	switch (ghost_type) {
	case RED: {
		type = RED;
		ScatterTarget[0] = level.GetSize(0) - 1;
		ScatterTarget[1] = 0;
		SetPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetNextPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
		SetInitialPosition(level.GetRedGhostXPos(), level.GetRedGhostYPos());
	}break;
	case PINK: {
		type = PINK;
		ScatterTarget[0] = 0;
		ScatterTarget[1] = 0;
		SetPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetNextPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
		SetInitialPosition(level.GetPinkGhostXPos(), level.GetPinkGhostYPos());
	}break;
	case BLUE: {
		type = BLUE;
		ScatterTarget[0] = level.GetSize(level.GetSize() - 1) - 1;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetNextPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
		SetInitialPosition(level.GetBlueGhostXPos(), level.GetBlueGhostYPos());
	}break;
	case ORANGE: {
		type = ORANGE;
		ScatterTarget[0] = 0;
		ScatterTarget[1] = level.GetSize() - 1;
		SetPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetNextPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
		SetInitialPosition(level.GetOrangeGhostXPos(), level.GetOrangeGhostYPos());
	}break;
	}
	//GHOST HOUSE TARGET
	if (level.GetHouseXPos() == 0 && level.GetHouseYPos() == 0) {
		initial_house.x = initial_position.x;
		initial_house.y = initial_position.y;
	}
	else {
		initial_house.x = level.GetHouseXPos();
		initial_house.y = level.GetHouseYPos();
	}
	//IDLE TARGET
	if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
		IdleTarget[0] = position.x + 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
		IdleTarget[0] = position.x - 1;
		IdleTarget[1] = position.y;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y - 1;
	}
	else if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y + 1;
	}
	else {
		IdleTarget[0] = position.x;
		IdleTarget[1] = position.y;
	}
	SetPixelPosition(level.GetPixelPositionX(GetPositionX()), level.GetPixelPositionY(GetPositionY()));
}

void Enemy::SetState(tState s)
{
	state = s;
}

void Enemy::SetPosition(int posX, int posY) {
	position.x = posX;
	position.y = posY;
}

void Enemy::SetNextPosition(int posX, int posY) {
	next_position.x = posX;
	next_position.y = posY;
}

void Enemy::SetInitialPosition(int posX, int posY) {
	initial_position.x = posX;
	initial_position.y = posY;
}

void Enemy::SetPixelPosition(float pixel_x, float pixel_y) {
	position.pixel_x = pixel_x;
	position.pixel_y = pixel_y;
}

void Enemy::Draw(float swidth, float sheight, int x, int y) {
	if (GetState() == FRIGHTENED) {
		drawSprite(scared_sprite[animationState], x, y, getSpriteWidth(scared_sprite[animationState]) / 2, getSpriteHeight(scared_sprite[animationState]) / 2, 0, swidth, sheight);
	}
	else if (GetState() == DEAD) {
		drawSprite(eaten_sprite[animationState], x, y, getSpriteWidth(scared_sprite[animationState]) / 2, getSpriteHeight(scared_sprite[animationState]) / 2, 0, swidth, sheight);
	}
	else {
		std::cerr << "BEFORE: " << animationState << '\n';
		drawSprite(sprite[animationState], x, y, getSpriteWidth(sprite[animationState]) / 2, getSpriteHeight(sprite[animationState]) / 2, 0, swidth, sheight);
		std::cerr << "AFTER: " << animationState << '\n';
	}
	animationState++;
	if (animationState >= 3) {
		animationState = 1;
	}
}

void Enemy::SetTarget(int targetX, int targetY) {
	target[0] = targetX;
	target[1] = targetY;
}

void Enemy::MoveToTarget(Level &level) {
	tDirection nextDir;
	float minimumDistance;
	int targetX, targetY;
	bool possible = false;

	//CHOOSE TARGET
	if (GetState() == CHASE) {
		targetX = target[0];
		targetY = target[1];
	}
	else if (GetState() == SCATTER) {
		targetX = ScatterTarget[0];
		targetY = ScatterTarget[1];
	}
	else if (GetState() == IDLE) {
		if (position.x == IdleTarget[0] && position.y == IdleTarget[1]) {
			targetX = initial_position.x;
			targetY = initial_position.y;
		}
		else {
			targetX = IdleTarget[0];
			targetY = IdleTarget[1];
		}
	}
	else if (GetState() == TRANSITION) {
		targetX = initial_house.x;
		targetY = initial_house.y;
	}
	else if (GetState() == DEAD) {
		targetX = initial_position.x;
		targetY = initial_position.y;
	}

	//CHOOSE NEXT DIRECTION
	//CHASE & SCATTER
	if (GetState() == CHASE || GetState() == SCATTER) {
		switch (direction) {
		case UP: { //If the last direction was UP, we only check UP, LEFT and RIGHT directions
			nextDir = UP;
			minimumDistance = HUGE_DISTANCE;

			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				//We set as the minimum distance the one that corresponds to the direction we are in.
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					//Only if the distance in other direction is lower than the one that was the minimum one we set this new direction as the movement one.
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
					nextDir = DOWN;
				}
				else {
					nextDir = NON;
				}
			}
		}
				 break;
		case DOWN: {
			nextDir = DOWN;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
					nextDir = UP;
				}
				else {
					nextDir = NON;
				}
			}
		}
				   break;
		case RIGHT: {
			nextDir = RIGHT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
					nextDir = LEFT;
				}
				else {
					nextDir = NON;
				}
			}
		}
					break;
		case LEFT: {
			nextDir = LEFT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
					nextDir = RIGHT;
				}
				else {
					nextDir = NON;
				}
			}
		}
		}
	}
	//IDLE
	if (GetState() == IDLE) {
		switch (direction) {
		case UP: { //If the last direction was UP, we only check UP, LEFT and RIGHT directions
			nextDir = UP;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				//We set as the minimum distance the one that corresponds to the direction we are in.
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					//Only if the distance in other direction is lower than the one that was the minimum one we set this new direction as the movement one.
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				nextDir = NON;
			}
		}
				 break;
		case DOWN: {
			nextDir = DOWN;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				//We set as the minimum distance the one that corresponds to the direction we are in.
				nextDir = UP;
				possible = true;
			}
			if (!possible) {
				nextDir = NON;
			}
		}
				   break;
		case RIGHT: {
			nextDir = RIGHT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				nextDir = NON;
			}
		}
					break;
		case LEFT: {
			nextDir = LEFT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				nextDir = NON;
			}
		}
		}
	}
	//TRANSITION & DEAD
	else if (GetState() == TRANSITION || GetState() == DEAD) {
		switch (direction) {
		case UP: { //If the last direction was UP, we only check UP, LEFT and RIGHT directions
			nextDir = UP;
			minimumDistance = HUGE_DISTANCE;

			if (movementPossible(level.GetMap(), position.x, position.y - 1, true)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				//We set as the minimum distance the one that corresponds to the direction we are in.
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y, true)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					//Only if the distance in other direction is lower than the one that was the minimum one we set this new direction as the movement one.
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y, true)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x, position.y + 1, true)) {
					nextDir = DOWN;
				}
				else {
					nextDir = NON;
				}
			}
		}
				 break;
		case DOWN: {
			nextDir = DOWN;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x + 1, position.y, true)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1, true)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y, true)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x, position.y - 1, true)) {
					nextDir = UP;
				}
				else {
					nextDir = NON;
				}
			}
		}
				   break;
		case RIGHT: {
			nextDir = RIGHT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1, true)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x + 1, position.y, true)) {
				if (minimumDistance > distance(position.x + 1, position.y, targetX, targetY)) {
					nextDir = RIGHT;
					minimumDistance = distance(position.x + 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1, true)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x - 1, position.y, true)) {
					nextDir = LEFT;
				}
				else {
					nextDir = NON;
				}
			}
		}
					break;
		case LEFT: {
			nextDir = LEFT;
			minimumDistance = HUGE_DISTANCE;
			if (movementPossible(level.GetMap(), position.x, position.y - 1, true)) {
				minimumDistance = distance(position.x, position.y - 1, targetX, targetY);
				nextDir = UP;
				possible = true;
			}
			if (movementPossible(level.GetMap(), position.x, position.y + 1, true)) {
				if (minimumDistance > distance(position.x, position.y + 1, targetX, targetY)) {
					nextDir = DOWN;
					minimumDistance = distance(position.x, position.y + 1, targetX, targetY);
					possible = true;
				}
			}
			if (movementPossible(level.GetMap(), position.x - 1, position.y, true)) {
				if (minimumDistance > distance(position.x - 1, position.y, targetX, targetY)) {
					nextDir = LEFT;
					minimumDistance = distance(position.x - 1, position.y, targetX, targetY);
					possible = true;
				}
			}
			if (!possible) {
				if (movementPossible(level.GetMap(), position.x + 1, position.y, true)) {
					nextDir = RIGHT;
				}
				else {
					nextDir = NON;
				}
			}
		}
		}
	}
	//DEAD
	else if (GetState() == FRIGHTENED) {
		int rand_aux = rand() % (3);
		switch (direction) {
		case UP: {
			if (rand_aux == 0) {
				if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else nextDir = NON;
			}
			else if (rand_aux == 1) {
				if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else nextDir = NON;
			}
			else if (rand_aux == 2) {
				if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else nextDir = NON;
			}
		}break;
		case RIGHT: { //RIGHT DOWN UP
			if (rand_aux == 0) {
				if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else nextDir = NON;
			}
			else if (rand_aux == 1) {
				if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else nextDir = NON;
			}
			else if (rand_aux == 2) {
				if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else nextDir = NON;
			}
		}break;
		case DOWN: {
			if (rand_aux == 0) {
				if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else nextDir = NON;
			}
			else if (rand_aux == 1) {
				if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else nextDir = NON;
			}
			else if (rand_aux == 2) {
				if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else nextDir = NON;
			}
		}break;
		case LEFT: {
			if (rand_aux == 0) {
				if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else nextDir = NON;
			}
			else if (rand_aux == 1) {
				if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else nextDir = NON;
			}
			else if (rand_aux == 2) {
				if (movementPossible(level.GetMap(), position.x, position.y + 1)) nextDir = DOWN;
				else if (movementPossible(level.GetMap(), position.x - 1, position.y)) nextDir = LEFT;
				else if (movementPossible(level.GetMap(), position.x, position.y - 1)) nextDir = UP;
				else if (movementPossible(level.GetMap(), position.x + 1, position.y)) nextDir = RIGHT;
				else nextDir = NON;
			}
		}break;
		}
	}

	//MAKING THE MOVEMENT

	int disp[2] = { 0,0 }, newPosX, newPosY;
	disp[0] = 0;
	disp[1] = 0;

	switch (nextDir) {
	case RIGHT: {
		disp[0] = 1;
	} break;
	case LEFT: {
		disp[0] = -1;
	} break;
	case UP: {
		disp[1] = -1;
	} break;
	case DOWN: {
		disp[1] = 1;
	} break;
	}

	newPosX = GetPositionX() + disp[0];
	newPosY = GetPositionY() + disp[1];
	CheckJump(level.GetMap(), newPosX, newPosY);
	SetNextPosition(newPosX, newPosY);
	direction = nextDir;
	//Finally, we set as the last direction the one in which we have made the movement, in order to consider it when making another mov.
}

void Enemy::SetCounter(int i) {	counter = i;}
void Enemy::SetStateCounter(int i) { state_counter = i; }
void Enemy::SetMaxCounter(int i) {	max_counter = i; }
void Enemy::ResetCounter() { counter = 1; }

ALLEGRO_BITMAP * Enemy::GetBitmap() const{ return sprite[animationState]; }

tDirection Enemy::GetDirection() const { return direction; }

int Enemy::GetPositionX() const{ return position.x; }
int Enemy::GetPositionY() const{ return position.y; }
int Enemy::GetNextPositionX() const { return next_position.x; }
int Enemy::GetNextPositionY() const { return next_position.y; }
int Enemy::GetInitialPositionX() const { return initial_position.x; }
int Enemy::GetInitialPositionY() const { return initial_position.y; }
int Enemy::GetHousePositionX() const { return initial_house.x; }
int Enemy::GetHousePositionY() const { return initial_house.y; }
int Enemy::GetCounter() const { return counter; }
int Enemy::GetStateCounter() const { return state_counter; }
int Enemy::GetIdleTime() const { return idle_time; }

float Enemy::GetPixelPositionX() const { return position.pixel_x; }
float Enemy::GetPixelPositionY() const { return position.pixel_y;}
float Enemy::GetMaxCounter() const { return max_counter; }

tState Enemy::GetState() const{	return state;}

tGhost Enemy::GetType() const {	return type; }

Enemy::~Enemy(){
	destroySprite(sprite);
	destroySprite(scared_sprite);
	destroySprite(eaten_sprite);
}

float distance(int posX, int posY, int targetX, int targetY) {	return hypot(posX-targetX, posY-targetY); }