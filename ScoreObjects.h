#ifndef SCOREOBJECTS_H
#define SCOREOBJECTS_H
#include <string>

struct playerData
{
	std::string name;
	Score score;
};

class Score {
	public:
		Score();
		
		void IncreaseScore(const long long int & value);

		int ReturnScore() const;

		~Score();
	private:
		long long int score;
};

class ScoreObject
{
	public:
		ScoreObject();

		~ScoreObject();

	protected:
		int value;
};

class Pellet : ScoreObject
{
public:
	Pellet();

	void Caught(Score s);

	~Pellet();
private:
	int value = 5;
};

class Bonus : ScoreObject
{
	public:
		Bonus();

		void Caught(Score s);

		~Bonus();
	private:
		int value = 150;
};


class PowerUp : ScoreObject
{
	public:
		PowerUp();

		void Caught(Score s);

		~PowerUp();
	private:
		int value = 50;
};

#endif
