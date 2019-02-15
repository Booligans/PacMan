#ifndef PLAYER_H
#define PLAYER_H
#include "Level_Load.h"
#include <set>
#include <vector>

// Pacman Timing: Each 0.136 seconds per position in the map. For each move, it's drawn 4 times.
// Updated at 7.35 FPS and drawn at 29.4 FPS

const int INITIAL_PACMAN_LIVES = 2;

enum tDirection { RIGHT, DOWN, LEFT, UP, NON };
const std::set<tGame_Element> ALLOWED_OBJECTS = { INITIAL, EMPTY, RED_GHOST, BLUE_GHOST, PINK_GHOST, ORANGE_GHOST, PLAYER, PELLET, POWER_UP, CHERRY, PINEAPPLE, WATERMELON, BONUS_POINT };

struct pixel_position {
	int x, y;
	float pixel_x, pixel_y;
};


const int PACMAN_ANIMATION_STAGES = 10;

class Player
{
public:
	Player(Level const& level, int mLives);

	void Reset(Level &level);
	void GameReset(Level &level, int l= INITIAL_PACMAN_LIVES);
	void SetDirection(tDirection direction);
	void SetNextDirection(tDirection next_direction);
	void SetLastDirection(tDirection last_direction);
	void SetDead(bool b);
	void SetAnimationState(int i);

	void ResetProgress();
	void IncreaseProgress();
	void SetPosition(const int & x, const int & y);
	void SetInitialPosition(const int & x, const int & y);
	void SetPixelPosition(float pixel_x, float pixel_y);
	void SetLives(const short int & l);
	void MovePlayer(std::vector<std::vector<tGame>> &map);
	void Draw(float swidth, float sheight, int x, int y);

	void SetCounter(int i);
	void SetDeadCounter(int i);
	void SetMaxCounter(int i);
	void ResetCounter();

	ALLEGRO_BITMAP *GetBitmap() const;
	tDirection GetDirection() const;
	tDirection GetNextDirection() const;
	tDirection GetLastDirection() const;
	int GetProgress() const;
	int GetLives() const;
	int GetPositionX() const;
	int GetPositionY() const;
	int GetInitialPositionX() const;
	int GetInitialPositionY() const;
	float GetPixelPositionX() const;
	float GetPixelPositionY() const;
	int GetAnimationState() const;
	int GetCounter() const;
	int GetMaxCounter() const;
	int GetDeadCounter() const;
	bool GetDead() const;

	~Player();
private:
	bool dead;
	int progress, max_lives;
	short int lives, animationState, counter;
	int max_counter, dead_counter;
	pixel_position initial_position, position;
	std::vector<ALLEGRO_BITMAP *> sprite;
	std::vector<ALLEGRO_BITMAP *> dead_sprite;
	tDirection dir, next_dir, last_dir;
};

void CheckJump(std::vector<std::vector<tGame>> & map, int & checkX, int & checkY);
bool movementPossible(std::vector<std::vector<tGame>> &map, int checkX, int checkY, bool ghost = false);
tDirection GetOppositeDirection(tDirection direction);

#endif