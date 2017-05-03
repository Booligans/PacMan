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
