#include "StudentWorld.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::~StudentWorld()
{
	list<Actor*>::iterator p = activeActors.begin();
	p++;
	while (p != activeActors.end())
	{
		Actor* temp = *p;
		p--;
		activeActors.remove(temp);
		delete temp;
		if (p != activeActors.end())
			p++;
	}
	p = activeActors.begin();
	Actor* temp = *p;
	activeActors.remove(temp);
	delete temp;
}

bool StudentWorld::checkWall(int x, int y, int level)
{
	Level lev(assetDirectory());
	Level::LoadResult result;
	switch (level)
	{
	case 0:
		result = lev.loadLevel("level00.dat");
		break;
	case 1:
		result = lev.loadLevel("level01.dat");
		break;
	case 2:
		result = lev.loadLevel("level02.dat");
		break;
	case 3:
		result = lev.loadLevel("level03.dat");
		break;
	case 4:
		result = lev.loadLevel("level04.dat");
		break;
	default:
		return false;
	}
	if (result == Level::load_fail_file_not_found)
		std::cerr << "Could not find data file\n";
	else if (result == Level::load_fail_bad_format)
		std::cerr << "Your level was improperly formatted\n";
	else if (result == Level::load_success)
	{
		Level::MazeEntry ge = lev.getContentsOf(x, y);
		switch (ge)
		{
		case Level::wall:
			return true;
		default:
			return false;
		}
	}
}

void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel();
	unsigned int bonus = levelBonus;
	int livesLeft = getLives(); 

	string s = format(score, level, livesLeft, player->healthPercentage(), player->ammunition(), bonus);

	setGameStatText(s);
}

string StudentWorld::format(int score, int level, int lives, int health, int ammo, unsigned int bonus)
{
	ostringstream oss;
	oss << "Score: ";
	oss.fill('0');
	oss << setw(7) << score;
	oss << "  Level: ";
	oss.fill('0');
	oss << setw(2) << level;
	oss << "  Lives: ";
	oss.fill(' ');
	oss << setw(2) << lives;
	oss << "  Health: ";
	oss << setw(3) << health;
	oss << "%  Ammo: ";
	oss << setw(3) << ammo;
	oss << "  Bonus: ";
	oss << setw(4) << bonus;
	return oss.str();
}

Actor* StudentWorld::allocate(int x, int y, int level)
{
	Actor* actor = nullptr;
	Level lev(assetDirectory());
	Level::LoadResult result;
	switch (level)
	{
	case 0:
		result = lev.loadLevel("level00.dat");
		break;
	case 1:
		result = lev.loadLevel("level01.dat");
		break;
	case 2:
		result = lev.loadLevel("level02.dat");
		break;
	case 3:
		result = lev.loadLevel("level03.dat");
		break;
	case 4:
		result = lev.loadLevel("level04.dat");
		break;
	default:
		return actor;
	}
	if (result == Level::load_fail_file_not_found)
		std::cerr << "Could not find data file\n";
	else if (result == Level::load_fail_bad_format)
		std::cerr << "Your level was improperly formatted\n";
	else if (result == Level::load_success)
	{
		Level::MazeEntry ge = lev.getContentsOf(x, y);
		switch (ge)
		{
		case Level::empty:
			return actor;
		case Level::wall:
			actor = new Wall(x, y, this);
			activeActors.push_back(actor);
			return actor;
		case Level::player:
			player = new Player(x, y, this);
			actor = player;
			activeActors.push_back(actor);
			return actor;
		default:
			return actor;
		}
	}
	return actor;
}

int StudentWorld::init()
{
	levelBonus = 1000;
	for (int i = 0; i < VIEW_WIDTH; i++)
	{
		for (int j = 0; j < VIEW_HEIGHT; j++)
		{
			allocate(i, j, getLevel());
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();
	// Update Display Text
	for (list<Actor*>::iterator p = activeActors.begin(); p != activeActors.end(); p++)
	{
		if ((*p)->isAlive())
		{
			(*p)->doSomething();
			
			if (player != nullptr && player->hitPoints() <= 0)
				player->setAlive(false);
			if (player != nullptr && !player->isAlive())
			{
				decLives();
				return GWSTATUS_PLAYER_DIED;
			}
			
		}

	}
	levelBonus--;
	//advanceToNextLevel();
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	list<Actor*>::iterator p = activeActors.begin();
	p++;
	while (p != activeActors.end())
	{
		Actor* temp = *p;
		p--;
		activeActors.remove(temp);
		delete temp;
		if (p != activeActors.end())
			p++;
	}
	p = activeActors.begin();
	Actor* temp = *p;
	activeActors.remove(temp);
	delete temp;
}