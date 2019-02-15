#include "Refresh_Draw.h"
#include "DataSave.h"

#include <iostream>
#include <cmath>

//First we create a window
//We load the scoreboards from the PLAYER_DATAPATH
//Now we load the UI elements
//We load the level progression
//We start the gameloop
//IF the game is lost the data of the current player is saved

//const float GENERAL_REFRESH_FPS = 29.4;

const int SIZE_LIMIT = 10;

int main()
{
	FreeConsole(); //Hides the console.
	srand(time(NULL)); //Random numbers.

	bool done = false, draw = false, nextLevel = false;
	playerArray data;
	playerData currentPlayer;
	std::string introduce_name = "";
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_TIMER *general_timer = nullptr;
	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
	ALLEGRO_COLOR back_color = al_map_rgb(0, 0, 0);

	//Initialize Program
	initializeFramework(true, true, false, true, true, true, 2);
	createDisplay(display, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "Pacman", standard);
	initializeEvent(display, event_queue, true, true, false);

	ALLEGRO_BITMAP *icon;

	ALLEGRO_PATH * path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Sprites");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	loadSprite(icon, "Pacman.svg.png");
	al_set_display_icon(display, icon);

	//Creating Classes
	Level level = Level();
	UserInterface UI;
	Player pacman(level, UI.getMaxLives());
	Enemy rg(RED, level);
	Enemy bg(BLUE, level);
	Enemy og(ORANGE, level);
	Enemy pg(PINK, level);

	//Load Player Data
	LoadAndDecryptFile(data);

	//Initial

	UI.drawUI();
	UI.refreshScoreboard(data);
	drawLevel(level, pacman, rg, pg, og, bg, back_color, SCREEN_WIDTH, SCREEN_HEIGHT);
	showScreen(back_color);

	//Set Timer

	createTimer(general_timer, GENERAL_REFRESH_FPS);
	registerTimer(event_queue, general_timer);
	startTimer(general_timer);

	//Game Loop

	while (!done) {
		ALLEGRO_EVENT events;
		waitEvent(event_queue, events);

		//Keyboard events
		if (events.type == EVENT_KEY_DOWN) {
			if (UI.GetNameDone()) {
				switch (events.keyboard.keycode) {
				case KEY_D:
				case KEY_RIGHT: {
					if (!(UI.GetPause() || UI.GetReset() || UI.GetGameOver() || pacman.GetDead())) {
						if (movementPossible(level.GetMap(), pacman.GetPositionX() + 1, pacman.GetPositionY())) {
							pacman.SetDirection(RIGHT);
						}
						pacman.SetNextDirection(RIGHT);
					}
				}break;
				case KEY_A:
				case KEY_LEFT: {
					if (!(UI.GetPause() || UI.GetReset() || UI.GetGameOver() || pacman.GetDead())) {
						if (movementPossible(level.GetMap(), pacman.GetPositionX() - 1, pacman.GetPositionY())) {
							pacman.SetDirection(LEFT);
						}
						pacman.SetNextDirection(LEFT);
					}
				}break;
				case KEY_W:
				case KEY_UP: {
					if (!(UI.GetPause() || UI.GetReset() || UI.GetGameOver() || pacman.GetDead())) {
						if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() - 1)) {
							pacman.SetDirection(UP);
						}
						pacman.SetNextDirection(UP);
					}
				}break;
				case KEY_S:
				case KEY_DOWN: {
					if (!(UI.GetPause() || UI.GetReset() || UI.GetGameOver() || pacman.GetDead())) {
						if (movementPossible(level.GetMap(), pacman.GetPositionX(), pacman.GetPositionY() + 1)) {
							pacman.SetDirection(DOWN);
						}
						pacman.SetNextDirection(DOWN);
					}
				}break;
				case KEY_P: {
					if (!UI.GetGameOver()) {
						if (UI.GetPause()) {
							UI.SetPause(false);
							UI.SetAudio(true);
							UI.PlayThisSong(UI.GetpacmanSongInstance());
						}
						else {
							UI.SetPause(true);
							UI.SetAudio(false);
						}
					}
				}break;
				case KEY_O: {
					UI.SetAudio(!UI.GetAudio());
				}break;
				case KEY_ENTER: {
					if (UI.GetGameOver()) {
						UI.SetGameOver(false);
						UI.SetReset(true);
						UI.SetResetCounter(2);
					}
				}break;
				case KEY_N: {
					nextLevel = true;
				}break;
				case KEY_ESCAPE: {
					done = true;
				}
				}
			}
			else {
				switch (events.keyboard.keycode) {
				case KEY_BACKSPACE: if (introduce_name.length() > 0) introduce_name.pop_back(); break;
				case KEY_ENTER: {
					UI.SetNameDone(true);
					if (introduce_name == "") introduce_name = "DEFAULT";
					UI.SetPlayerName(introduce_name);
					introduce_name = "";
					UI.SetReset(true, false);
				} break;
				case KEY_ESCAPE: {
					done = true;
				} break;
				default: {
					if (KEY_A <= events.keyboard.keycode &&  events.keyboard.keycode <= KEY_Z) { 
						if (introduce_name.size() < SIZE_LIMIT) 
							introduce_name += events.keyboard.keycode - KEY_A + 'A'; 
					}
					else if (KEY_0 <= events.keyboard.keycode && events.keyboard.keycode <= KEY_9) {
						if (introduce_name.size() < SIZE_LIMIT)
							introduce_name += events.keyboard.keycode - KEY_0 + '0';
					}
				}
				}
				if (!UI.GetNameDone()) UI.SetPlayerName(introduce_name);
			}
		}

		//Display events
		else if (events.type == EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		//Timer Events
		else if (events.type == EVENT_TIMER) {
			draw = true;
			if (UI.GetNameDone()) {
				if (!UI.GetPause() && !UI.GetReset() && !UI.GetGameOver()) {
					refreshLevel(level, pacman, rg, pg, og, bg, UI);

					if (pacman.GetProgress() >= level.GetObjective() || nextLevel)
					{
							level.NextLevel();
							rg.UpdatePositions(level);
							bg.UpdatePositions(level);
							og.UpdatePositions(level);
							pg.UpdatePositions(level);

							UI.increaseLevel();
							UI.SetReset(true, false);
							pacman.GameReset(level, pacman.GetLives());
							//pacman.ResetProgress();
							nextLevel = false;
					}

				}
				else if (UI.GetReset() && !UI.GetPause()) {
					UI.SetAudio(false);
					if (UI.GetResetCounter() == 1) {
						UI.MakeReset(level, pacman, rg, pg, og, bg);
					}
					if (UI.GetResetCounter() < RESET_COUNTER_MAX) {
						UI.SetResetCounter(UI.GetResetCounter() + 1);
					}
					else {
						UI.SetAudio(true);
						UI.PlayThisSong(UI.GetpacmanSongInstance());
						UI.SetResetCounter(1);
						UI.SetReset(false);
					}
				}
				else if (UI.GetGameOver() && UI.GetAuxGameOver()) {
					UI.SetAudio(false);
					currentPlayer.name = UI.GetPlayerName();
					currentPlayer.score = UI.score;
					AddData(data, currentPlayer);
					UI.MakeGameOver(level, pacman, rg, pg, og, bg);
					UI.SetAuxGameOver(false);
					level.setCurrentLevel(1);
					UI.SetCurrentLevel(1);
				}
			}
		}

		if (draw) {
			UI.drawUI();
			UI.refreshScoreboard(data);
			drawLevel(level, pacman, rg, pg, og, bg, back_color, SCREEN_WIDTH, SCREEN_HEIGHT);
			if (UI.GetReset() && !UI.GetPause()) {
				UI.drawReset();
			}
			if (UI.GetGameOver()) {
				UI.drawGameOver();
			}
			if (UI.GetPause() && !UI.GetGameOver()) {
				UI.drawPause();
			}
			if (!UI.GetNameDone()) {
				UI.drawName();
			}
			showScreen(back_color);
			draw = false;
		}
	}

	//Saving Data
	SaveAndEncrypt(data);

	//Destroying program
	al_destroy_bitmap(icon);
	destroyFramework(true, true, false, true, true, true);

	return 0;
}