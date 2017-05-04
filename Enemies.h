#ifndef ENEMIES_H
#define ENEMIES_H

typedef enum tState { IDLE, SCATTER, CHASE, FRIGHTENED };

class Enemy
{
	public:
		//Constructors
		Enemy();

		//Methods
		void SetState(tState s);
		void SetPosition(int posX, int posY);
		void SetTarget(int targetX, int targetY);
		void MoveToTarget();

		tState GetState() const;

		//Destructor
		~Enemy();
	private:
		tState state;
	protected:
		int target[2];
		int position[2];
};

class RedGhost : Enemy
{
	public:
		RedGhost(int posX, int posY, int targetX, int targetY);

		~RedGhost();
	private:
		int redScatterTarget[2];

};

class PinkGhost : Enemy
{
	public:
		PinkGhost(int posX, int posY, int targetX, int targetY);

		~PinkGhost();
	private:
		int pinkScatterTarget[2];
};

class OrangeGhost : Enemy
{
	public:
		OrangeGhost(int posX, int posY, int targetX, int targetY);

		~OrangeGhost();
	private:
		int orangeScatterTarget[2];

};

class BlueGhost : Enemy
{
	public:
		BlueGhost(int posX, int posY, int targetX, int targetY);

		~BlueGhost();
	private:
		int blueScatterTarget[2];
};

//Here go the external functions needed 

#endif
