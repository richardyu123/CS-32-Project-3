#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <list>
#include <string>

class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
		player = nullptr;
		levelBonus = 1000;
	}

	~StudentWorld();

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	bool checkWall(int x, int y, int level);

private:
	Player* player;
	std::list<Actor*> activeActors;
	void setDisplayText();
	std::string format(int score, int level, int lives, int health, int ammo, unsigned int bonus);
	Actor* allocate(int x, int y, int level);
	void removeDead();
	unsigned int levelBonus;
};

#endif // STUDENTWORLD_H_