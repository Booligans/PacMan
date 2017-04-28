#ifndef ENEMIES_H
#define ENEMIES_H

typedef enum Type{Red_Ghost, Pink_Ghost, Orange_Ghost, Scared_Ghost};

class Enemy
{
	public:
		//Constructors
		Enemy();
		//Methods
		void ChasePLayer(Type t);
		//Destructor
		~Enemy();
	private:
		Type type;
};

//Here go the external functions needed 

#endif