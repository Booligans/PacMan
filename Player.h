#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		Player(const short int & l, const long long int & s);

		const int ReturnLives();

		~Player();
	private:
		short int lives;
};

#endif