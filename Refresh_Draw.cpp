#include "Refresh_Draw.h"

//USER INTERFACE

UserInterface::UserInterface() {
	MAX_LIVES = 5;
	next_goal = 1000;

	name_done = false;
	audio = true;
	loadSong(pacmanSong, "PacmanSong.wav", songInstance, loop);
	loadSound(pacmanFX, "Pacman_FX.wav");
	LoadAndDecryptFile(topScores);

	pause = false;
	loadFont(font_pause, "Pixeled.ttf", 50);
	reset = false;
	loadFont(font_reset, "Pixeled.ttf", 30);
	reset_counter = 1;
	game_over = false;
	aux_gameover = true;
	loadFont(font_gameover, "Pixeled.ttf", 50);
	loadFont(font_gameover_text, "Pixeled.ttf", 20);

	loadFont(ghost_dead, "Pixeled.ttf", 10);

	loadSprite(livesUI, "UI_Lives.png");
	UI_LIVES_POS_X = SCREEN_WIDTH * 1 / 16;
	UI_LIVES_POS_Y = SCREEN_HEIGHT * 1 / 12;
	swidth_UI_lives = (SCREEN_WIDTH * 1 / 8) / getSpriteWidth(livesUI);
	sheight_UI_lives = (SCREEN_HEIGHT * 1 / 12) / getSpriteHeight(livesUI);

	loadSprite(life, "Life_Icon.png");

	swidth_initial_life = 0.9*(swidth_UI_lives);
	sheight_initial_life = 0.8*(sheight_UI_lives);
	UI_LIFE_WIDTH = 0.9*swidth_initial_life*al_get_bitmap_width(livesUI) / MAX_LIVES;
	UI_LIFE_XBASE = UI_LIVES_POS_X+0.3*(swidth_initial_life*al_get_bitmap_width(livesUI) / MAX_LIVES);
	UI_LIFE_Y = UI_LIVES_POS_Y + 0.7*al_get_bitmap_height(livesUI);

	loadSprite(controlsUI, "UI_Controls.png");
	CONTROLS_POS_X = SCREEN_WIDTH * 1 / 16;
	CONTROLS_POS_Y = SCREEN_HEIGHT * 1 / 4;
	swidth_controls = (SCREEN_WIDTH * 1 / 8) / getSpriteWidth(controlsUI);
	sheight_controls = (SCREEN_HEIGHT * 2 / 3) / getSpriteHeight(controlsUI);


	loadSprite(levelBannerUI, "UI_Level_Banner.png");
	loadFont(font1, "Pixeled.ttf", 30);
	LEVEL_BANNER_POS_X = SCREEN_WIDTH * 1 / 4;
	LEVEL_BANNER_POS_Y = SCREEN_HEIGHT * 1 / 12;
	swidth_level_banner = (SCREEN_WIDTH * 1 / 2) / getSpriteWidth(levelBannerUI);
	sheight_level_banner = (SCREEN_HEIGHT * 1 / 12) / getSpriteHeight(levelBannerUI);
	LEVEL_TEXT_CONSTRAINT_X = 0.5f;
	LEVEL_TEXT_CONSTRAINT_Y = 0.5f;
	LEVEL_TEXT_POS_X = LEVEL_BANNER_POS_X + LEVEL_TEXT_CONSTRAINT_X*swidth_level_banner*al_get_bitmap_width(levelBannerUI);
	LEVEL_TEXT_POS_Y = LEVEL_BANNER_POS_Y - LEVEL_TEXT_CONSTRAINT_Y*al_get_bitmap_height(levelBannerUI);

	loadSprite(scoreUI, "UI_Score.png");
	loadFont(font2, "Pixeled.ttf", 20);
	SCORE_POS_X = SCREEN_WIDTH * 13 / 16;
	SCORE_POS_Y = SCREEN_HEIGHT * 1 / 12;
	swidth_score = (SCREEN_WIDTH * 1 / 8) / getSpriteWidth(scoreUI);
	sheight_score = (SCREEN_HEIGHT * 1 / 12) / getSpriteHeight(scoreUI);
	SCORE_TEXT_CONSTRAINT_X = 0.97f;
	SCORE_TEXT_CONSTRAINT_Y = 0.05f;
	SCORE_TEXT_POS_X = SCORE_POS_X + SCORE_TEXT_CONSTRAINT_X*swidth_score*al_get_bitmap_width(scoreUI);
	SCORE_TEXT_POS_Y = SCORE_POS_Y + SCORE_TEXT_CONSTRAINT_Y*sheight_score*al_get_bitmap_height(scoreUI);

	loadSprite(scoreBoardUI, "UI_Scoreboard.png");
	loadFont(font3, "Pixeled.ttf", 10);
	SCOREBOARD_POS_X = SCREEN_WIDTH * 13 / 16.0f;
	SCOREBOARD_POS_Y = SCREEN_HEIGHT / 4.0f;
	swidth_scoreboard = (SCREEN_WIDTH / 8.0f) / getSpriteWidth(scoreBoardUI);
	sheight_scoreboard = (SCREEN_HEIGHT * 2 / 3.0f) / getSpriteHeight(scoreBoardUI);
	TOPSCORES_CONSTRAINT_X = 0.1f;
	TOPSCORES_CONSTRAINT_Y = 0.15f;
	TOPSCORES_POS_X = SCOREBOARD_POS_X + TOPSCORES_CONSTRAINT_X*swidth_scoreboard*al_get_bitmap_width(scoreBoardUI);
	TOPSCORES_POS_Y = SCOREBOARD_POS_Y + TOPSCORES_CONSTRAINT_Y*sheight_scoreboard*al_get_bitmap_height(scoreBoardUI);
	TOPSCORES_JUMP_X = 0.6*al_get_bitmap_width(scoreBoardUI);
	TOPSCORES_JUMP_Y = 0.08*sheight_scoreboard*al_get_bitmap_height(scoreBoardUI);
	TOPSCORES_SCORE_POS_X = TOPSCORES_POS_X + getSpriteWidth(scoreBoardUI)*swidth_scoreboard*0.85;
	TOPSCORES_SCORE_POS_Y = TOPSCORES_POS_Y;

	loadSprite(controlsUI_sound,"UI_Controls_sound.png");
	loadSprite(controlsUI_muted, "UI_Controls_muted.png");

	currentLevel = 1;
	numLives = INITIAL_PACMAN_LIVES;
}

int UserInterface::getMaxLives() const {
	return MAX_LIVES;
}

int UserInterface::getNextGoal() const {
	return next_goal;
}

void UserInterface::advanceGoal() {
	next_goal = 2 * next_goal;
}

void UserInterface::drawUI() {

	//DRAW LIVES
	drawSprite(livesUI, UI_LIVES_POS_X, UI_LIVES_POS_Y, swidth_UI_lives, sheight_UI_lives);

	for (int i = 0; i < numLives; i++) {
		drawSprite(life, UI_LIFE_XBASE + i * UI_LIFE_WIDTH, UI_LIFE_Y, swidth_initial_life, sheight_initial_life);
	}

	if (audio) {
		drawSprite(controlsUI_sound, CONTROLS_POS_X, CONTROLS_POS_Y, swidth_controls, sheight_controls);
	}
	else {
		drawSprite(controlsUI_muted, CONTROLS_POS_X, CONTROLS_POS_Y, swidth_controls, sheight_controls);
	}

	drawSprite(levelBannerUI, LEVEL_BANNER_POS_X, LEVEL_BANNER_POS_Y, swidth_level_banner, sheight_level_banner);

	if (name_done) {
		drawFont(font1, al_map_rgb(0, 0, 0), LEVEL_TEXT_POS_X, LEVEL_TEXT_POS_Y, ALLIGN_CENTRE, "Level " + std::to_string(currentLevel)); //The sprite needs to be updated
	}
	else {
		drawFont(font1, al_map_rgb(0, 0, 0), LEVEL_TEXT_POS_X, LEVEL_TEXT_POS_Y, ALLIGN_CENTRE, playerName); //The sprite needs to be updated
	}

	drawSprite(scoreUI, SCORE_POS_X, SCORE_POS_Y, swidth_score, sheight_score);
	drawFont(font2, al_map_rgb(0, 0, 0), SCORE_TEXT_POS_X, SCORE_TEXT_POS_Y, ALLIGN_RIGHT, std::to_string(score.ReturnScore()));

	drawSprite(scoreBoardUI, SCOREBOARD_POS_X, SCOREBOARD_POS_Y, swidth_scoreboard, sheight_scoreboard);
}

void UserInterface::SetCurrentLevel(int l) {
	currentLevel = l;
}

void UserInterface::PlayThisSound(ALLEGRO_SAMPLE * sound) {
	if (audio) playSound(sound, once);
}

void UserInterface::PlayThisSong(ALLEGRO_SAMPLE_INSTANCE * instance) {
	if (audio) {
		playSong(instance);
	}
}

void UserInterface::StopThisSong(ALLEGRO_SAMPLE_INSTANCE * instance) {
	stopSong(instance);
}

void UserInterface::copyLives(int l) {
	numLives = l;
}

void UserInterface::increaseLevel()
{
	currentLevel++;
}

void UserInterface::refreshScoreboard(const playerArray & p)
{
	topScores = p;
	for (int i = 0; i < (int)topScores.size(); i++) {
		drawFont(font3, al_map_rgb(0, 0, 0), TOPSCORES_POS_X, TOPSCORES_POS_Y + TOPSCORES_JUMP_Y*i, ALLIGN_LEFT, topScores[i].name);
		drawFont(font3, al_map_rgb(0, 0, 0), TOPSCORES_POS_X + TOPSCORES_JUMP_X, TOPSCORES_POS_Y + TOPSCORES_JUMP_Y*i, ALLIGN_RIGHT, std::to_string(topScores[i].score.ReturnScore()));
	}
}

void UserInterface::SetPause(bool option) {
	pause = option;
}

void UserInterface::SetGameOver(bool option) {
	game_over = option;
}

void UserInterface::SetAuxGameOver(bool option) {
	aux_gameover = option;
}

void UserInterface::SetReset(bool option, bool lowerLives) {
	reset = option;
	lower_lives = lowerLives;
}

void UserInterface::SetResetCounter(int i) {
	reset_counter = i;
}

void UserInterface::SetAudio(bool option) {
	audio = option;
	if (!option) {
		stopSong(songInstance); //Stop all the music and sound.
	}
	else {
		PlayThisSong(songInstance);
	}
}

void UserInterface::MakeReset(Level &level, Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg) {
	if(lower_lives) pacman.SetLives(pacman.GetLives()-1);
	copyLives(pacman.GetLives());

	pacman.Reset(level);
	rg.Reset(level);
	pg.Reset(level);
	og.Reset(level);
	bg.Reset(level);
}

void UserInterface::MakeGameOver(Level &level, Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg) {
	level.GameReset();
	next_goal = 500;
	pacman.GameReset(level);
	copyLives(pacman.GetLives());
	rg.GameReset(RED, level);
	pg.GameReset(PINK, level);
	og.GameReset(ORANGE, level);
	bg.GameReset(BLUE, level);
	score.SetScore(0);
}

void UserInterface::drawGameOver()
{
	drawFont(font_gameover, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5, ALLIGN_CENTRE, "GAME OVER");
	drawFont(font_gameover_text, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 5, ALLIGN_CENTRE, "PRESS ENTER TO RESTART THE GAME");
}

void UserInterface::drawPause() {
	drawFont(font_pause, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5, ALLIGN_CENTRE, "GAME PAUSED");
}

void UserInterface::drawReset() {
	drawFont(font_reset, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5, ALLIGN_CENTRE, "READY!");
}

void UserInterface::drawGhostDead(int i, int j, int num) {
	drawFont(ghost_dead, al_map_rgb(255, 255, 255), i, j, ALLIGN_CENTRE, std::to_string(num));
}

bool UserInterface::GetPause() const { return pause;}
bool UserInterface::GetGameOver() const { return game_over; }
bool UserInterface::GetAuxGameOver() const { return aux_gameover; }
bool UserInterface::GetReset() const { return reset; }
bool UserInterface::GetAudio() const { return audio; }
int UserInterface::GetResetCounter() const { return reset_counter; }
ALLEGRO_SAMPLE_INSTANCE * UserInterface::GetpacmanSongInstance() const { return songInstance; }
ALLEGRO_SAMPLE * UserInterface::GetpacmanFXSound() const { return pacmanFX; }

UserInterface::~UserInterface() {
	destroySprite(life);
	destroySprite(livesUI);
	destroySprite(scoreUI);
	destroySprite(scoreBoardUI);
	destroySprite(levelBannerUI);
	destroySprite(controlsUI);
}

//REFRESHING
void refreshLevel(Level &level, Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg, UserInterface &UI) {
	//PACMAN ALIVE
	if (!pacman.GetDead()) {
		//Refresh Pacman
		if (pacman.GetCounter() >= pacman.GetMaxCounter()) {
			pacmanRefreshPosition(level, pacman, rg, pg, og, bg, UI);
		}
		else {
			pacmanRefreshPixel(level, pacman);
		}
		pacman.SetAnimationState(pacman.GetAnimationState() + 1);

		//Refresh Ghosts
		//RED GHOST
		if (rg.GetCounter() >= rg.GetMaxCounter()) {
			ghostRefreshPosition(level, rg, pacman, rg);
		}
		else {
			ghostRefreshPixel(level, rg, pacman);
		}
		ghostRefreshState(rg);

		//PINK GHOST
		if (pg.GetCounter() >= pg.GetMaxCounter()) {
			ghostRefreshPosition(level, pg, pacman, rg);
		}
		else {
			ghostRefreshPixel(level, pg, pacman);
		}
		ghostRefreshState(pg);

		//ORANGE GHOST
		if (og.GetCounter() >= og.GetMaxCounter()) {
			ghostRefreshPosition(level, og, pacman, rg);
		}
		else {
			ghostRefreshPixel(level, og, pacman);
		}
		ghostRefreshState(og);

		//BLUE GHOST
		if (bg.GetCounter() >= bg.GetMaxCounter()) {
			ghostRefreshPosition(level, bg, pacman, rg);
		}
		else {
			ghostRefreshPixel(level, bg, pacman);
		}
		ghostRefreshState(bg);

		//Check Collision
		checkCollision(pacman, rg, pg, og, bg, UI);

		//Refresh Bonus
		level.RefreshBonus();

	}
	//PACMAN DEAD
	else {
		UI.SetAudio(false);
		if (pacman.GetAnimationState() >= 10) {
			if (pacman.GetLives() > 0) {
				UI.SetReset(true);
				UI.SetGameOver(false);
			}
			else {
				UI.SetGameOver(true);
				UI.SetAuxGameOver(true);
				UI.SetReset(false);
			}
		}
		else {
			if (pacman.GetDeadCounter() % (DEAD_ANIMATION_COUNTER_MAX / 10) == 0) {
				pacman.SetAnimationState(pacman.GetAnimationState() + 1);
			}
			pacman.SetDeadCounter(pacman.GetDeadCounter() + 1);
		}
	}
}

void pacmanRefreshPosition(Level &level, Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg, UserInterface &UI) {
	tGame_Element aux = MISTAKE;

	level.SetMapElem(pacman.GetPositionY(), pacman.GetPositionX(), EMPTY);
	pacman.MovePlayer(level.GetMap());
	aux = level.GetElement(pacman.GetPositionY(), pacman.GetPositionX());

	//Refresh score
	if (aux == PELLET)
	{
		UI.score.IncreaseScore(1);
		pacman.IncreaseProgress();
	}
	else if (aux == POWER_UP)
	{
		UI.score.IncreaseScore(5);
		pacman.IncreaseProgress();

		if (!(rg.GetState() == DEAD || rg.GetState() == IDLE || rg.GetState() == TRANSITION)) {
			rg.SetState(FRIGHTENED);
			rg.SetMaxCounter(8);
			rg.SetStateCounter(1);
		}

		if (!(pg.GetState() == DEAD || pg.GetState() == IDLE || pg.GetState() == TRANSITION)) {
			pg.SetState(FRIGHTENED);
			pg.SetMaxCounter(8);
			pg.SetStateCounter(1);
		}

		if (!(og.GetState() == DEAD || og.GetState() == IDLE || og.GetState() == TRANSITION)) {
			og.SetState(FRIGHTENED);
			og.SetMaxCounter(8);
			og.SetStateCounter(1);
		}

		if (!(bg.GetState() == DEAD || bg.GetState() == IDLE || bg.GetState() == TRANSITION)) {
			bg.SetState(FRIGHTENED);
			bg.SetMaxCounter(8);
			bg.SetStateCounter(1);
		}

	}
	else if (aux == CHERRY)
	{
		UI.score.IncreaseScore(25);
	}
	else if (aux == PINEAPPLE) {
		UI.score.IncreaseScore(50);
	}
	else if (aux == WATERMELON) {
		UI.score.IncreaseScore(100);
	}

	if (UI.score.ReturnScore() >= UI.getNextGoal()) {
		pacman.SetLives(pacman.GetLives() + 1);
		UI.advanceGoal();
		UI.copyLives(pacman.GetLives());
	}

	level.SetMapElem(pacman.GetPositionY(), pacman.GetPositionX(), PLAYER);
	pacman.ResetCounter();
}

void pacmanRefreshPixel(Level &level, Player &pacman) {
	bool draw_dir = false;

	switch (pacman.GetNextDirection()) {
	case RIGHT: {
		if (movementPossible(level.GetMap(), pacman.GetPositionX() + 1, pacman.GetPositionY()) && !(pacman.GetDirection() == GetOppositeDirection(pacman.GetNextDirection()))) {
			pacman.SetPixelPosition(pacman.GetPixelPositionX() + level.GetRowPixelElem() / pacman.GetMaxCounter(), pacman.GetPixelPositionY());
		}
		else {
			draw_dir = true;
		}
	} break;
	case LEFT: {
		if (movementPossible(level.GetMap(), pacman.GetPositionX() - 1, pacman.GetPositionY()) && !(pacman.GetDirection() == GetOppositeDirection(pacman.GetNextDirection()))) {
			pacman.SetPixelPosition(pacman.GetPixelPositionX() - level.GetRowPixelElem() / pacman.GetMaxCounter(), pacman.GetPixelPositionY());
		}
		else {
			draw_dir = true;
		}
	} break;
	case UP: {
		if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() - 1) && !(pacman.GetDirection() == GetOppositeDirection(pacman.GetNextDirection()))) {
			pacman.SetPixelPosition(pacman.GetPixelPositionX(), pacman.GetPixelPositionY() - level.GetColumnPixelElem() / pacman.GetMaxCounter());
		}
		else {
			draw_dir = true;
		}
	} break;
	case DOWN: {
		if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() + 1) && !(pacman.GetDirection() == GetOppositeDirection(pacman.GetNextDirection()))) {
			pacman.SetPixelPosition(pacman.GetPixelPositionX(), pacman.GetPixelPositionY() + level.GetColumnPixelElem() / pacman.GetMaxCounter());
		}
		else {
			draw_dir = true;
		}
	} break;
	case NON: {
		draw_dir = true;
	}
	}

	if (draw_dir) {
		switch (pacman.GetDirection()) {
		case RIGHT: {
			if (movementPossible(level.GetMap(), pacman.GetPositionX() + 1, pacman.GetPositionY())) {
				pacman.SetPixelPosition(pacman.GetPixelPositionX() + level.GetRowPixelElem() / pacman.GetMaxCounter(), pacman.GetPixelPositionY());
			}
		} break;
		case LEFT: {
			if (movementPossible(level.GetMap(), pacman.GetPositionX() - 1, pacman.GetPositionY())) {
				pacman.SetPixelPosition(pacman.GetPixelPositionX() - level.GetRowPixelElem() / pacman.GetMaxCounter(), pacman.GetPixelPositionY());
			}
		} break;
		case UP: {
			if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() - 1)) {
				pacman.SetPixelPosition(pacman.GetPixelPositionX(), pacman.GetPixelPositionY() - level.GetColumnPixelElem() / pacman.GetMaxCounter());
			}
		} break;
		case DOWN: {
			if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() + 1)) {
				pacman.SetPixelPosition(pacman.GetPixelPositionX(), pacman.GetPixelPositionY() + level.GetColumnPixelElem() / pacman.GetMaxCounter());
			}
		} break;
		}
	}
	pacman.SetCounter(pacman.GetCounter() + 1);
}

void ghostRefreshPosition(Level &level, Enemy &enemy, Player &pacman, Enemy &rg) {
	int add_x = 0, add_y = 0;
	switch (enemy.GetType()) {
	case RED: {
		enemy.SetTarget(pacman.GetPositionX(), pacman.GetPositionY());
	}break;
	case PINK: {
		switch (pacman.GetDirection()) {
		case UP: add_y = -4; break;
		case RIGHT: add_x = 4; break;
		case DOWN: add_y = 4; break;
		case LEFT: add_x = -4; break;
		}
		enemy.SetTarget(pacman.GetPositionX() + add_x, pacman.GetPositionY() + add_y);
	}break;
	case BLUE: {
		switch (pacman.GetDirection()) {
		case UP: add_y = -2; break;
		case RIGHT: add_x = 2; break;
		case DOWN: add_y = 2; break;
		case LEFT: add_x = -2; break;
		}
		int tile_x, tile_y, vector_x, vector_y;
		tile_x = pacman.GetPositionX() + add_x;
		tile_y = pacman.GetPositionY() + add_y;

		vector_x = abs(rg.GetPositionX() - tile_x);
		vector_y = abs(rg.GetPositionY() - tile_y);

		if (rg.GetPositionX() >= tile_x) {
			vector_x = -vector_x;
		}
		if (rg.GetPositionY() >= tile_y) {
			vector_y = -vector_y;
		}

		enemy.SetTarget(tile_x + vector_x, tile_y + vector_y);
	}break;
	case ORANGE: {
		if (distance(enemy.GetPositionX(), enemy.GetPositionY(), pacman.GetPositionX(), pacman.GetPositionY()) > 8) 	enemy.SetTarget(pacman.GetPositionX(), pacman.GetPositionY());
		else {
			enemy.SetTarget(1, 29);
		}
	}break;
	}

	enemy.SetPosition(enemy.GetNextPositionX(), enemy.GetNextPositionY());
	enemy.SetPixelPosition(level.GetPixelPositionX(enemy.GetPositionX()), level.GetPixelPositionY(enemy.GetPositionY()));
	enemy.MoveToTarget(level);
	enemy.ResetCounter();
}

void ghostRefreshPixel(Level &level, Enemy &enemy, Player &pacman) {
	float row_pixel_increment = level.GetRowPixelElem() / enemy.GetMaxCounter();
	float column_pixel_increment = level.GetColumnPixelElem() / enemy.GetMaxCounter();

	switch (enemy.GetDirection()) {
	case RIGHT: {
		enemy.SetPixelPosition(enemy.GetPixelPositionX() + row_pixel_increment, enemy.GetPixelPositionY());
	} break;
	case LEFT: {
		enemy.SetPixelPosition(enemy.GetPixelPositionX() - row_pixel_increment, enemy.GetPixelPositionY());
	} break;
	case UP: {
		enemy.SetPixelPosition(enemy.GetPixelPositionX(), enemy.GetPixelPositionY() - column_pixel_increment);
	} break;
	case DOWN: {
		enemy.SetPixelPosition(enemy.GetPixelPositionX(), enemy.GetPixelPositionY() + column_pixel_increment);
	} break;
	}
	enemy.SetCounter(enemy.GetCounter() + 1);
}

void ghostRefreshState(Enemy &enemy) {
	//Counter number = seconds / (1/FPS);
	float timer_fps = 1 / GENERAL_REFRESH_FPS;
	int scatter_time = 7 / timer_fps;
	int chase_time = 20 / timer_fps;
	int frightened_time = 10 / timer_fps;
	int idle_time = enemy.GetIdleTime() / timer_fps;

	if (enemy.GetStateCounter() >= scatter_time && enemy.GetState() == SCATTER) {
		enemy.SetState(CHASE);
		enemy.SetStateCounter(1);
	}
	else if (enemy.GetStateCounter() >= chase_time && enemy.GetState() == CHASE) {
		enemy.SetState(SCATTER);
		enemy.SetStateCounter(1);
	}
	else if ((enemy.GetStateCounter() >= frightened_time && enemy.GetState() == FRIGHTENED) || (enemy.GetNextPositionX() == enemy.GetHousePositionX() && enemy.GetNextPositionY() == enemy.GetHousePositionY() && enemy.GetState() == TRANSITION)) {
		enemy.SetState(CHASE);
		enemy.SetMaxCounter(4);
		enemy.SetStateCounter(1);
	}
	else if ((enemy.GetNextPositionX() == enemy.GetInitialPositionX() && enemy.GetNextPositionY() == enemy.GetInitialPositionY() && enemy.GetState() == DEAD) || (enemy.GetStateCounter() >= idle_time && enemy.GetState() == IDLE)) {
		enemy.SetState(TRANSITION);
		enemy.SetMaxCounter(8);
		enemy.SetStateCounter(1);
	}
	enemy.SetStateCounter(enemy.GetStateCounter() + 1);
}

void checkCollision(Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg, UserInterface &UI) {
	bool rg_collision = collisionBox(pacman.GetBitmap(), pacman.GetPixelPositionX(), pacman.GetPixelPositionY(), rg.GetBitmap(), rg.GetPixelPositionX(), rg.GetPixelPositionY());
	bool pg_collision = collisionBox(pacman.GetBitmap(), pacman.GetPixelPositionX(), pacman.GetPixelPositionY(), pg.GetBitmap(), pg.GetPixelPositionX(), pg.GetPixelPositionY());
	bool og_collision = collisionBox(pacman.GetBitmap(), pacman.GetPixelPositionX(), pacman.GetPixelPositionY(), og.GetBitmap(), og.GetPixelPositionX(), og.GetPixelPositionY());
	bool bg_collision = collisionBox(pacman.GetBitmap(), pacman.GetPixelPositionX(), pacman.GetPixelPositionY(), bg.GetBitmap(), bg.GetPixelPositionX(), bg.GetPixelPositionY());

	if (rg_collision) {
		if (rg.GetState() == CHASE || rg.GetState() == SCATTER) {
			pacman.SetDead(true);
			pacman.SetAnimationState(1);
		}
		else if (rg.GetState() == FRIGHTENED) {
			rg.SetState(DEAD);
			UI.score.IncreaseScore(numDeadGhost(rg, pg, og, bg) * 25);
			rg.SetMaxCounter(4);
		}
	}
	if (pg_collision) {
		if (pg.GetState() == CHASE || pg.GetState() == SCATTER) {
			pacman.SetDead(true);
			pacman.SetAnimationState(1);
		}
		else if (pg.GetState() == FRIGHTENED) {
			pg.SetState(DEAD);
			UI.score.IncreaseScore(numDeadGhost(rg, pg, og, bg) * 25);
			pg.SetMaxCounter(4);
		}
	}
	if (og_collision) {
		if (og.GetState() == CHASE || og.GetState() == SCATTER) {
			pacman.SetDead(true);
			pacman.SetAnimationState(1);
		}
		else if (og.GetState() == FRIGHTENED) {
			og.SetState(DEAD);
			UI.score.IncreaseScore(numDeadGhost(rg, pg, og, bg) * 25);
			og.SetMaxCounter(4);
		}
	}
	if (bg_collision) {
		if (bg.GetState() == CHASE || bg.GetState() == SCATTER) {
			pacman.SetDead(true);
			pacman.SetAnimationState(1);
		}
		else if (bg.GetState() == FRIGHTENED) {
			bg.SetState(DEAD);
			UI.score.IncreaseScore(numDeadGhost(rg, pg, og, bg) * 25);
			bg.SetMaxCounter(4);
		}
	}
}

int numDeadGhost(Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg) {
	int numDead = 0;
	if (rg.GetState() == DEAD) {
		numDead++;
	}
	if (pg.GetState() == DEAD) {
		numDead++;
	}
	if (bg.GetState() == DEAD) {
		numDead++;
	}
	if (og.GetState() == DEAD) {
		numDead++;
	}
	return numDead;
}

//DRAWING

void drawLevel(Level &level, Player &pacman, Enemy &rg, Enemy &pg, Enemy &og, Enemy &bg, ALLEGRO_COLOR back_color, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	float swidth, sheight;

	for (int i = 0; i < level.GetSize(); i++)
	{
		for (int j = 0; j < level.GetSize(i); j++)
		{
			swidth = level.GetRowPixelElem() / getSpriteWidth(level.GetBitmap(i, j));
			sheight = level.GetColumnPixelElem() / getSpriteHeight(level.GetBitmap(i, j));

			if (level.GetElement(i, j) != PLAYER && level.GetElement(i, j) != RED_GHOST && level.GetElement(i, j) != BLUE_GHOST && level.GetElement(i, j) != PINK_GHOST && level.GetElement(i, j) != ORANGE_GHOST)
			{
				drawSprite(level.GetBitmap(i, j), level.GetPixelPositionX(j), level.GetPixelPositionY(i), getSpriteWidth(level.GetBitmap(i, j)) / 2, getSpriteHeight(level.GetBitmap(i, j)) / 2, level.AngleFromElement(level.GetElement(i, j)), swidth, sheight);
			}
			else if (level.GetElement(i, j) == PLAYER) {
				pacman.Draw(swidth, sheight, pacman.GetPixelPositionX(), pacman.GetPixelPositionY());
				rg.Draw(swidth, sheight, rg.GetPixelPositionX(), rg.GetPixelPositionY());
				pg.Draw(swidth, sheight, pg.GetPixelPositionX(), pg.GetPixelPositionY());
				og.Draw(swidth, sheight, og.GetPixelPositionX(), og.GetPixelPositionY());
				bg.Draw(swidth, sheight, bg.GetPixelPositionX(), bg.GetPixelPositionY());
			}

		}
	}
}

void UserInterface::SetPlayerName(std::string name) {
	playerName = name;
}

void UserInterface::drawName() {
	drawFont(font_pause, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 7, ALLIGN_CENTRE, "INTRODUCE");
	drawFont(font_pause, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5, ALLIGN_CENTRE, "YOUR");
	drawFont(font_pause, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 4, ALLIGN_CENTRE, "NICKNAME");
}

bool UserInterface::GetNameDone() const {
	return name_done;
}

std::string UserInterface::GetPlayerName() const {
	return playerName;
}

void UserInterface::SetNameDone(bool option) {
	name_done = option;
}

