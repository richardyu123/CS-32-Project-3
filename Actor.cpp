#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, int startX, int startY, int hitPoints, StudentWorld* world, Direction startDirection)
	:GraphObject(imageID, startX, startY, startDirection)
{
	m_hitPoints = hitPoints;
	m_world = world;
	m_alive = true;
	setVisible(true);
}

//==========================Player================================

Player::Player(int startX, int startY, StudentWorld* world)
	: Actor(IID_PLAYER, startX, startY, 20, world, right)
{
	m_unition = 20;
}

void Player::doSomething()
{
	if (!isAlive())
		return;
	int ch;
	if (getWorld()->getKey(ch))
	{
		// user hit a key this tick!
		switch (ch)
		{
		case KEY_PRESS_ESCAPE:
			setAlive(false);
			break;
		case KEY_PRESS_LEFT:
			setDirection(left);
			if (!getWorld()->checkWall(getX() - 1, getY(), getWorld()->getLevel()))
			{
				moveTo(getX() - 1, getY());
			}
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if (!getWorld()->checkWall(getX() + 1, getY(), getWorld()->getLevel()))
			{
				moveTo(getX() + 1, getY());
			}
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if (!getWorld()->checkWall(getX(), getY() + 1, getWorld()->getLevel()))
			{
				moveTo(getX(), getY() + 1);
			}
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			if (!getWorld()->checkWall(getX(), getY() - 1, getWorld()->getLevel()))
			{
				moveTo(getX(), getY() - 1);
			}
			break;
		case KEY_PRESS_SPACE:
			//... add a Bullet in the square in front of the Player...;
			break;
		}
	}
}

int Player::attacked()
{
	decrementHP(2);
	if (hitPoints() > 0)
		return SOUND_PLAYER_IMPACT;
	else
		setAlive(false);
	return SOUND_PLAYER_DIE;
}

int Player::healthPercentage()
{
	return (100 * static_cast<int>(hitPoints() / 20.0));
}

//=================Wall========================

Wall::Wall(int startX, int startY, StudentWorld* world)
	:Actor(IID_WALL, startX, startY, 1, world)
{}


// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
