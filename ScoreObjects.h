#ifndef SCOREOBJECTS_H
#define SCOREOBJECTS_H

class Score {
	public:
		Score();
		
		void IncreaseScore(const int & value);

		const int ReturnScore();

		~Score();
	private:
		long long int score;
};

#endif