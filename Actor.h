#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, int hitPoints,
		StudentWorld* world, Direction startDirection = none);
	virtual ~Actor() {}
	virtual void doSomething() {}
	virtual int attacked() = 0;
	bool isAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }
	StudentWorld* getWorld() { return m_world; }
	int incrementHP(int amount);
	int decrementHP(int amount);
	int hitPoints() { return m_hitPoints; }
private:
	StudentWorld* m_world;
	bool m_alive;
	int m_hitPoints;
};

inline
int Actor::incrementHP(int amount)
{
	m_hitPoints += amount;
	return m_hitPoints;
}

inline
int Actor::decrementHP(int amount)
{
	m_hitPoints -= amount;
	return m_hitPoints;
}

class Player : public Actor
{
public:
	Player(int startX, int startY, StudentWorld* world);
	virtual void doSomething();
	virtual int attacked();
	int healthPercentage();
	void addAmmuntion(int added);
	int ammunition() { return m_unition; }
private:
	int m_unition;
};

class Wall : public Actor
{
public:
	Wall(int startX, int startY, StudentWorld* world);
	virtual int attacked() { return 1; }
};


#endif // ACTOR_H_
