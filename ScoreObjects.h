#ifndef SCOREOBJECTS_H
#define SCOREOBJECTS_H

#include "BoolEngine\BoolEngine.h"

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
//PLAYER INFORMATION
//	Player Score
class Score {
public:
	Score();

	void SetScore(const long long int & value);
	void IncreaseScore(const long long int & value);

	int ReturnScore() const;

	~Score();
private:
	long long int score;
};
//	Player Data
struct playerData
{
	std::string name;
	Score score;
};

// Vector of Players Data
typedef std::vector<playerData> playerArray;
bool operator < (const playerData & p1, const playerData & p2);
bool operator == (const playerData &p1, const playerData &p2);
bool operator > (const playerData &p1, const playerData &p2);
void AddData(playerArray & a, const playerData & p);

#endif