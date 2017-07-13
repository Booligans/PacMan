#ifndef PLAYER_H
#define PLAYER_H
#include "Level_Load.h"

typedef enum tTecla { UP, DOWN, LEFT, RIGHT, EXIT};

class Player
{
	public:
		Player(const short int & l, const long long int & s);

		void SetPosition(const int & x,const int & y);
		void SetLives(const short int & l);
		void MovePlayer(const tTecla & dir, tGame_Element **map);

		int ReturnLives() const;
		int GetPositionX() const;
		int GetPositionY() const;

		~Player();
	private:
		short int lives;
		int position[2];
};

tTecla leerTecla()
{
	tTecla aux;
	//Aquí se lee del input organizado por el motor
	return aux;
}

bool movementPossible(int x, int y, tTecla dir, tGame_Element **map, const int disp[2]);


#endif
