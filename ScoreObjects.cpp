#include "ScoreObjects.h"

Score::Score()
{}

void Score::SetScore(const long long int & value)
{
	score = value;
}

void Score::IncreaseScore(const long long int & value)
{
	score += value;
}

int Score::ReturnScore() const
{
	return score;
}

Score::~Score()
{}

ScoreObject::ScoreObject()
{}
ScoreObject::~ScoreObject()
{}

Pellet::Pellet()
{
	ScoreObject();
}

void Pellet::Caught(Score s)
{
	s.IncreaseScore(value);
	Pellet::~Pellet();
}

Pellet::~Pellet()
{
	ScoreObject::~ScoreObject();
}

Bonus::Bonus()
{
	ScoreObject();
}

void Bonus::Caught(Score s)
{
	s.IncreaseScore(value);
	Bonus::~Bonus();
}

Bonus::~Bonus()
{
	ScoreObject::~ScoreObject();
}

PowerUp::PowerUp()
{

}

void PowerUp::Caught(Score s)
{

}

PowerUp::~PowerUp()
{

}
