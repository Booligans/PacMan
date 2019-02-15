#include "ScoreObjects.h"

Score::Score(){	SetScore(0);}
void Score::SetScore(const long long int & value){	score = value; }
void Score::IncreaseScore(const long long int & value){	score += value; }
int Score::ReturnScore() const{	return score;}
Score::~Score(){}
bool operator < (const playerData & p1, const playerData & p2){	return (p1.score.ReturnScore() < p2.score.ReturnScore() || (p1.score.ReturnScore() == p2.score.ReturnScore() && p1.name < p2.name)); }
bool operator == (const playerData &p1, const playerData &p2) { return (p1.score.ReturnScore() == p2.score.ReturnScore() && (p1.name == p2.name)); }
bool operator > (const playerData &p1, const playerData &p2) { return !(p1 < p2 || p1 == p2); }

void AddData(playerArray & a, const playerData & p)
{
	int i = a.size() - 1;
	bool stop = false;
	a.push_back(p);
	std::sort(a.begin(), a.end(), std::greater<playerData>());
}