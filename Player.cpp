#include "Player.h"

Player::Player(Level const& level, int mLives)
{
	dead = false;
	lives = INITIAL_PACMAN_LIVES;
	max_lives = mLives;
	SetCounter(0);
	SetDeadCounter(0);
	SetMaxCounter(4);
	animationState = 1;
	progress = 0;

	dir = LEFT;
	next_dir = LEFT;
	last_dir = NON;

	loadSprite(sprite, "Pac-Man_AnimationSheet.png", PACMAN_ANIMATION_STAGES, 1);
	loadSprite(dead_sprite, "Pacman_Death_Animation.png", PACMAN_ANIMATION_STAGES, 1);

	SetInitialPosition(level.GetPacmanXPos(), level.GetPacmanYPos());
	SetPosition(level.GetPacmanXPos(), level.GetPacmanYPos());
	SetPixelPosition(level.GetPixelPositionX(GetPositionX()), level.GetPixelPositionY(GetPositionY()));
}

void Player::Reset(Level &level) {
	dead = false;
	SetCounter(0);

	SetMaxCounter(4);
	animationState = 1;

	SetPosition(GetInitialPositionX(), GetInitialPositionY());
	SetPixelPosition(level.GetPixelPositionX(GetInitialPositionX()), level.GetPixelPositionY(GetInitialPositionY()));
	level.SetMapElem(GetPositionY(), GetPositionX(), PLAYER);

	dir = LEFT;
	next_dir = LEFT;
	last_dir = NON;
}

void Player::GameReset(Level &level, int l) {
	dead = false;
	lives = l;
	SetCounter(0);
	SetDeadCounter(0);
	SetMaxCounter(4);
	animationState = 1;
	ResetProgress();

	dir = LEFT;
	next_dir = LEFT;
	last_dir = NON;

	SetInitialPosition(level.GetPacmanXPos(), level.GetPacmanYPos());
	SetPosition(level.GetPacmanXPos(), level.GetPacmanYPos());
	SetPixelPosition(level.GetPixelPositionX(GetPositionX()), level.GetPixelPositionY(GetPositionY()));
}

void Player::SetDirection(tDirection direction) { dir = direction; }
void Player::SetNextDirection(tDirection next_direction) { next_dir = next_direction; }
void Player::SetLastDirection(tDirection last_direction) {	last_dir = last_direction; }
void Player::SetDead(bool b) {	dead = b; }
void Player::SetAnimationState(int i)
{
	animationState = i;
	if (animationState > 10) {
		animationState = animationState % PACMAN_ANIMATION_STAGES;
	}
}
void Player::SetCounter(int i) { counter = i; }
void Player::SetDeadCounter(int i) { dead_counter = i; }
void Player::SetMaxCounter(int i) { max_counter = i; }
void Player::ResetCounter() { counter = 1; }
void Player::ResetProgress(){ progress = 0; }
void Player::IncreaseProgress(){ progress++; }
void Player::SetPosition(const int & x, const int & y){
	position.x = x;
	position.y = y;
}
void Player::SetInitialPosition(const int & x, const int & y) {
	initial_position.x = x;
	initial_position.y = y;
}
void Player::SetPixelPosition(float pixel_x, float pixel_y) {
	position.pixel_x = pixel_x;
	position.pixel_y = pixel_y;
}
void Player::SetLives(const short int & l){	lives = min(l, max_lives); }

void Player::MovePlayer(std::vector<std::vector<tGame>> &map)
{
	bool move = true;
	int disp[2] = { 0,0 }, newPosX, newPosY;

	switch (next_dir) {
	case RIGHT: { disp[0] = 1; } break;
	case LEFT: { disp[0] = -1; } break;
	case UP: { disp[1] = -1; } break;
	case DOWN: { disp[1] = 1; } break;
	case NON: {	move = false; }
	}

	newPosX = GetPositionX() + disp[0];
	newPosY = GetPositionY() + disp[1];

	if (movementPossible(map, newPosX, newPosY) && move)
	{
		if (!(dir == GetOppositeDirection(next_dir)))
		{
			CheckJump(map, newPosX, newPosY);
			SetPosition(newPosX, newPosY);
			SetPixelPosition(map[GetPositionY()][GetPositionX()].pixel_position[0], map[GetPositionY()][GetPositionX()].pixel_position[1]);
			dir = next_dir;
		}
		next_dir = NON;
	}
	else
	{
		disp[0] = 0;
		disp[1] = 0;
		switch (dir) {
		case RIGHT: { disp[0] = 1; } break;
		case LEFT: { disp[0] = -1; } break;
		case UP: { disp[1] = -1; } break;
		case DOWN: { disp[1] = 1; } break;
		}

		newPosX = GetPositionX() + disp[0];
		newPosY = GetPositionY() + disp[1];

		if (movementPossible(map, newPosX, newPosY))
		{
			CheckJump(map, newPosX, newPosY);
			SetPosition(newPosX, newPosY);
			SetPixelPosition(map[GetPositionY()][GetPositionX()].pixel_position[0], map[GetPositionY()][GetPositionX()].pixel_position[1]);
		}
	}
}

void Player::Draw(float swidth, float sheight, int x, int y) {
	if (!dead) drawSprite(sprite[animationState], x, y, getSpriteWidth(sprite[animationState]) / 2, getSpriteHeight(sprite[animationState]) / 2, dir * PI / 2, swidth, sheight);
	else drawSprite(dead_sprite[animationState], x, y, getSpriteWidth(dead_sprite[animationState]) / 2, getSpriteHeight(dead_sprite[animationState]) / 2, dir * PI / 2, swidth, sheight);
}

ALLEGRO_BITMAP * Player::GetBitmap() const { return sprite[GetAnimationState()]; }
tDirection Player::GetDirection() const { return dir; }
tDirection Player::GetNextDirection() const { return next_dir; }
tDirection Player::GetLastDirection() const { return last_dir; }
int Player::GetProgress() const { return progress; }
int Player::GetLives() const { return lives; }
int Player::GetPositionX() const { return position.x; }
int Player::GetPositionY() const { return position.y; }
int Player::GetInitialPositionX() const { return initial_position.x; }
int Player::GetInitialPositionY() const { return initial_position.y; }
float Player::GetPixelPositionX() const { return position.pixel_x; }
float Player::GetPixelPositionY() const { return position.pixel_y; }
int Player::GetAnimationState() const {	return animationState; }
int Player::GetCounter() const { return counter; }
int Player::GetDeadCounter() const { return dead_counter; }
int Player::GetMaxCounter() const { return max_counter; }
bool Player::GetDead() const { return dead; }

Player::~Player() {	
	destroySprite(sprite); 
	destroySprite(dead_sprite);
}

bool movementPossible(std::vector<std::vector<tGame>> &map, int checkX, int checkY, bool ghost) {
	bool possible;

	CheckJump(map, checkX, checkY);
	if (ALLOWED_OBJECTS.count(map[checkY][checkX].elem) || 
		((map[checkY][checkX].elem == MISTAKE) && ghost == true)) 
		possible = true;
	else possible = false;
	return possible;
}

void CheckJump(std::vector<std::vector<tGame>> & map, int & checkX, int & checkY)
{
	if (checkY < 0)	checkY = map.size() - 1;
	else if (checkX < 0) checkX = map[checkY].size() - 1;
	else if (checkY == map.size()) checkY = 0;
	else if (checkX == map[checkY].size()) checkX = 0;
}

tDirection GetOppositeDirection(tDirection direction) {
	tDirection opposite = NON;

	switch (direction) {
	case RIGHT: {
		opposite = LEFT;
	}break;
	case LEFT: {
		opposite = RIGHT;
	}break;
	case DOWN: {
		opposite = UP;
	}break;
	case UP: {
		opposite = DOWN;
	}break;
	}
	return opposite;
}