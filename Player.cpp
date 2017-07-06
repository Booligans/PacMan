#include "Player.h"

Player::Player(const short int & l, const long long int & s)
{
	lives = l;
}

void Player::SetPosition(const int & x,const int & y)
{
	position[0] = x;
	position[1] = y;
}

void Player::SetLives(const short int & l)
{
	lives = l;
}

void Player::MovePlayer(const tTecla & dir, tGame_Element **map)
{
	int disp[2] = { 0,0 };
	switch (dir)
	{
	case UP: {
		disp[1] = 1;
	}
			 break;
	case DOWN: {
		disp[1] = -1;
	}
			   break;
	case LEFT: {
		disp[0] = -1;
	}
			   break;
	case RIGHT: {
		disp[0] = 1;
	}
	}
	if (movementPossible(GetPositionX(), GetPositionY(), dir, map, disp)) {
		SetPosition(GetPositionX() + disp[0], GetPositionY() + disp[1]) ;
	}
}

int Player::ReturnLives() const
{
	return lives;
}

int Player::GetPositionX() const
{
	return position[0];
}

int Player::GetPositionY() const
{
	return position[1];
}

Player::~Player()
{}

bool movementPossible(int x, int y, tTecla dir, tGame_Element **map, const int disp[2])
{
	bool possible;
	if (ALLOWED_OBJECTS.count(map[x + disp[0]][y + disp[1]]) != 0) possible = true;
	else possible = false;
	return possible;
}
