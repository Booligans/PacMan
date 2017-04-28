#include "Player.h"

Player::Player(const short int & l, const long long int & s)
{
	lives = l;
	score = s;
}

Player::~Player()
{}

const int Player::ReturnLives()
{
	return lives;
}
