#include "Level_Load.h"

Level::Level()
{
	currentLevel = 1;
	bonus_counter = 0;
	std::ifstream file;
	std::string line;

	ALLEGRO_PATH * path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Maps");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	file.open("config.txt");
	if (file.is_open()) {
		std::getline(file, line);
		num_map = std::stoi(line);
	}
	file.close();
	LoadLevel();
}

int Level::GetNumMap() const { return num_map; }
void Level::setCurrentLevel(int l) { currentLevel = min(1+l%num_map, l); }
void Level::GameReset() 
{ 
	currentLevel = 1;
	LoadLevel();
}

void Level::LoadLevel()
{
	std::ifstream file;
	std::string line;
	char char_aux;
	float max_row = 0;
	tGame aux;
	std::vector<tGame> vector_aux;
	objective = 0;
	map.clear();
	house_pos[0] = 0;
	house_pos[1] = 0;

	ALLEGRO_PATH * path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Maps");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	int mIndex = (currentLevel >= num_map) ? 1+((currentLevel-1) % num_map) : currentLevel;

	file.open("Level_" + std::to_string(mIndex) + ".lv"); //currentLevel is an integer 
	if (file.is_open()) {
		while (!file.eof()) {
			std::getline(file, line);
			if (line != "") {
				for (int i = 0; i < (int)line.length(); i++) {
					char_aux = line[i];
					aux.elem = CharacterTransform(char_aux);
					aux.sprite = GameElementToBitmap(aux.elem);
					vector_aux.push_back(aux);
				}
				map.push_back(vector_aux);
				vector_aux.clear();
			}
		}
	}
	file.close();
	for (int i = 0; i < (int)map.size(); i++) {
		if (map[i].size() > max_row) {
			max_row = map[i].size();
		}
	}
	row_pixel_elem = LEVEL_LENGTH_X / max_row;
	column_pixel_elem = LEVEL_LENGTH_Y / map.size();

	for (int i = 0; i < (int)map.size(); i++) {
		for (int j = 0; j < (int)map[i].size(); j++) {
			map[i][j].pixel_position[0] = INITIAL_LEVEL_POS_X + j*row_pixel_elem;
			map[i][j].pixel_position[1] = INITIAL_LEVEL_POS_Y + i*column_pixel_elem;
			if (map[i][j].elem == PELLET || map[i][j].elem == POWER_UP)
			{
				objective++;
			}
			else if (map[i][j].elem == PLAYER)
			{
				pacman_pos[1] = i;
				pacman_pos[0] = j;
			}
			else if (map[i][j].elem == RED_GHOST) {
				rg_pos[1] = i;
				rg_pos[0] = j;
			}
			else if (map[i][j].elem == BLUE_GHOST) {
				bg_pos[1] = i;
				bg_pos[0] = j;
			}
			else if (map[i][j].elem == PINK_GHOST) {
				pg_pos[1] = i;
				pg_pos[0] = j;
			}
			else if (map[i][j].elem == ORANGE_GHOST) {
				og_pos[1] = i;
				og_pos[0] = j;
			}
			else if (map[i][j].elem == INITIAL) {
				house_pos[1] = i;
				house_pos[0] = j;
			}
			else if (map[i][j].elem == BONUS_POINT) {
				bonus_pos[1] = i;
				bonus_pos[0] = j;
			}
		}
	}
}

void Level::NextLevel() {
	currentLevel++;
	LoadLevel();
}

void Level::SetMapElem(int i, int j, tGame_Element elem)
{
	destroySprite(map[i][j].sprite);
	map[i][j].sprite = nullptr;
	map[i][j].elem = elem;
	map[i][j].sprite = GameElementToBitmap(map[i][j].elem);
}

tGame_Element Level::CharacterTransform(const char& c) {
	tGame_Element aux;
	switch (c)
	{
	case 'a': aux = CLOSED_WALL;
		break;
	case 'b': aux = HORIZ_OPEN_WALL;
		break;
	case 'c': aux = VERT_OPEN_WALL;
		break;
	case 'd': aux = CLOSED_WALL_3_0DEG;
		break;
	case 'e': aux = CLOSED_WALL_3_90DEG;
		break;
	case 'f': aux = CLOSED_WALL_3_180DEG;
		break;
	case 'g': aux = CLOSED_WALL_3_270DEG;
		break;
	case 'h': aux = CLOSED_WALL_2_0DEG;
		break;
	case 'i': aux = CLOSED_WALL_2_90DEG;
		break;
	case 'j': aux = CLOSED_WALL_2_180DEG;
		break;
	case 'k': aux = CLOSED_WALL_2_270DEG;
		break;
	case 'l': aux = CLOSED_WALL_1_0DEG;
		break;
	case 'm': aux = CLOSED_WALL_1_90DEG;
		break;
	case 'n': aux = CLOSED_WALL_1_180DEG;
		break;
	case 'o': aux = CLOSED_WALL_1_270DEG;
		break;
	case 'p': aux = INTERIOR_WALL;
		break;
	case 'q': aux = BLUE_GHOST;
		break;
	case 'r': aux = RED_GHOST;
		break;
	case 's': aux = ORANGE_GHOST;
		break;
	case 't': aux = PINK_GHOST;
		break;
	case 'u': aux = CHERRY;
		break;
	case 'v': aux = PINEAPPLE;
		break;
	case 'w': aux = WATERMELON;
		break;
	case 'y': aux = CHERRY;
		break;
	case 'P': aux = PLAYER;
		break;
	case 'I': aux = INITIAL;
		break;
	case 'B': aux = BONUS_POINT;
		break;
	case '.': aux = PELLET;
		break;
	case '+': aux = POWER_UP;
		break;
	case ' ': aux = EMPTY;
		break;
	case '_':aux = EMPTY_WALL;
		break;
	default:
		aux = MISTAKE;
	}
	return aux;
}

ALLEGRO_BITMAP* Level::GameElementToBitmap(const tGame_Element elem)
{
	ALLEGRO_BITMAP * aux = nullptr;

	ALLEGRO_PATH * path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Sprites");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	switch (elem)
	{
	case INTERIOR_WALL:
	{ loadSprite(aux, "Inner_Wall.png"); }break;
	case CLOSED_WALL:
	{ loadSprite(aux, "Wall_Unique.png"); }break;
	case VERT_OPEN_WALL:
	case HORIZ_OPEN_WALL:
	{ loadSprite(aux, "Inner_Wall.png"); }break;
	case CLOSED_WALL_1_0DEG:
	case CLOSED_WALL_1_90DEG:
	case CLOSED_WALL_1_180DEG:
	case CLOSED_WALL_1_270DEG:
	{ loadSprite(aux, "Wall_Onesided.png"); }break;
	case CLOSED_WALL_2_0DEG:
	case CLOSED_WALL_2_90DEG:
	case CLOSED_WALL_2_180DEG:
	case CLOSED_WALL_2_270DEG:
	{ loadSprite(aux, "Wall_Corner.png"); }break;
	case CLOSED_WALL_3_0DEG:
	case CLOSED_WALL_3_90DEG:
	case CLOSED_WALL_3_180DEG:
	case CLOSED_WALL_3_270DEG:
	{ loadSprite(aux, "Wall_Corner.png"); }break;
	case PELLET:
	{ loadSprite(aux, "Pellet.png"); }break;
	case POWER_UP:
	{ loadSprite(aux, "PowerUp.png"); }break;
	case CHERRY:
	{ loadSprite(aux, "Cherries.png"); }break;
	case PINEAPPLE:
	{ loadSprite(aux, "Pineapple.png"); }break;
	case WATERMELON:
	{ loadSprite(aux, "Watermelon.png"); }break;
	case BONUS_POINT:
	case PLAYER:
	case INITIAL:
	case RED_GHOST:
	case BLUE_GHOST:
	case PINK_GHOST:
	case ORANGE_GHOST:
	case EMPTY_WALL:
	case EMPTY:
	{ loadSprite(aux, "Empty.png");	}break;
	default: { loadSprite(aux, "Error.png"); }
	}

	return aux;
}

float Level::AngleFromElement(const tGame_Element & aux)
{
	float angle;

	switch (aux)
	{
	case VERT_OPEN_WALL:
	case CLOSED_WALL_1_90DEG:
	case CLOSED_WALL_2_90DEG:
	case CLOSED_WALL_3_90DEG:
	{ angle = PI / 2.0; }break;
	case CLOSED_WALL_1_180DEG:
	case CLOSED_WALL_2_180DEG:
	case CLOSED_WALL_3_180DEG:
	{ angle = PI; }break;
	case CLOSED_WALL_1_270DEG:
	case CLOSED_WALL_2_270DEG:
	case CLOSED_WALL_3_270DEG:
	{ angle = (3 * PI) / 2.0; }break;
	default: { angle = 0; }
	}
	return angle;
}

void Level::IncreaseLevel()
{ 
	currentLevel++;
	LoadLevel();
}

void Level::ResetBonusCounter() { bonus_counter = 0; }
void Level::SetBonusCounter(int i) { bonus_counter = i; }
void Level::RefreshBonus() 
{ 
	float bonus_time = 15 / (1 / 29.4);
	if (bonus_counter >= bonus_time) {
		int num = rand() % 7;
		if (!(bonus_pos[0] == 0 && bonus_pos[1] == 0)) {
			if (num >= 0 && num < 4) { SetMapElem(bonus_pos[1], bonus_pos[0], CHERRY); }
			else if (num >= 4 && num < 6) { SetMapElem(bonus_pos[1], bonus_pos[0], PINEAPPLE); }
			else { SetMapElem(bonus_pos[1], bonus_pos[0], WATERMELON); }
		}
		SetBonusCounter(0);
	}
	if ((GetElement(bonus_pos[1], bonus_pos[0]) == EMPTY || GetElement(bonus_pos[1], bonus_pos[0]) == BONUS_POINT)) {
		SetBonusCounter(GetBonusCounter() + 1);
	}
}

int Level::GetCurrentLevel() const{ return currentLevel; }
int Level::GetSize(int i) const {
	if (i == -1) return map.size();
	else return map[i].size();
}

int Level::GetObjective() const{ return objective; }
tGame_Element Level::GetElement(int i, int j) const{ return map[i][j].elem; }
ALLEGRO_BITMAP * Level::GetBitmap(int i, int j) const{ return map[i][j].sprite; }
float Level::GetPixelPositionX(int j) const { return map[0][j].pixel_position[0]; }
float Level::GetPixelPositionY(int i) const { return map[i][0].pixel_position[1]; }
std::vector<std::vector<tGame>> Level::GetMap() const {	return map; }
int Level::GetRowPixelElem() const { return row_pixel_elem; }
int Level::GetColumnPixelElem() const {	return column_pixel_elem; }
int Level::GetBonusCounter() const { return bonus_counter; }
int Level::GetPacmanXPos() const{ return pacman_pos[0]; }
int Level::GetPacmanYPos() const{ return pacman_pos[1]; }
int Level::GetRedGhostXPos() const { return rg_pos[0]; }
int Level::GetRedGhostYPos() const { return rg_pos[1]; }
int Level::GetPinkGhostXPos() const { return pg_pos[0]; }
int Level::GetPinkGhostYPos() const { return pg_pos[1]; }
int Level::GetOrangeGhostXPos() const { return og_pos[0]; }
int Level::GetOrangeGhostYPos() const { return og_pos[1]; }
int Level::GetBlueGhostXPos() const { return bg_pos[0]; }
int Level::GetBlueGhostYPos() const { return bg_pos[1]; }
int Level::GetHouseXPos() const { return house_pos[0]; }
int	Level::GetHouseYPos() const { return house_pos[1]; }

void Level::destroyMap() {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			destroySprite(map[i][j].sprite);
		}
	}
	map.clear();
}

Level::~Level() { destroyMap(); }