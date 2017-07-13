#ifndef LEVEL_LOAD
#define LEVEL_LOAD
#include <string>
#include <fstream>
#include <set>

const std::string LEVEL_PATH = "levels.lv";

typedef enum tGame_Element {
	CLOSED_WALL, HORIZ_OPEN_WALL, VERT_OPEN_WALL, CLOSED_WALL_3_0DEG, CLOSED_WALL_3_90DEG, CLOSED_WALL_3_180DEG,
	CLOSED_WALL_3_270DEG, CLOSED_WALL_2_0DEG, CLOSED_WALL_2_90DEG, CLOSED_WALL_2_180DEG, CLOSED_WALL_2_270DEG,
	INTERIOR_WALL, CLOSED_WALL_1_0DEG, CLOSED_WALL_1_90DEG, CLOSED_WALL_1_180DEG, CLOSED_WALL_1_270DEG, PELLET, 
	POWER_UP, PLAYER, RED_GHOST, BLUE_GHOST, ORANGE_GHOST, PINK_GHOST, CHERRY, PINEAPPLE, ERROR
};

std::set <tGame_Element> ALLOWED_OBJECTS = { PELLET, POWER_UP, PLAYER, RED_GHOST, BLUE_GHOST, ORANGE_GHOST, PINK_GHOST, CHERRY, PINEAPPLE};

class Level
{
	public:
		Level();

		void LoadLevel(const int & r, const int & c);
		void SetSize(const int & r, const int & c);

		int GetRow() const;
		int GetCol() const;

		~Level();
	private:
		int col, row;
		tGame_Element **elem;
};

tGame_Element CharacterTransform(const char& c);




//Here we need

#endif
