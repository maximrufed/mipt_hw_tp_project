#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <set>

#include "tank.h"
#include "bullet.h"
#include "bulletBasicTimer.h"
#include "wall.h"
#include "weapon.h"
#include "weaponBullet.h"
#include "classData.h"
#include "contactListener.h"

class BasicGame
{
private:
	b2Vec2 gravity_;
	b2World world_;
	std::vector<Tank> tanks_;
	std::vector<Wall> walls_;
	std::vector<Bullet *> bullets_;
	// std::vector<Bonus> bonuses_;

	int nextTankID_ = 0;
	int nextWeaponID_ = 0;
	int nextBulletID_ = 0;

	int sizeFieldX_ = 8;
	int sizeFieldY_ = 6;
	float cellSize_ = 100;
	const float wallWidth_ = 2;
	void addWallBetweenCells(int x1, int y1, int x2, int y2);
	void addWall(float x1, float y1, float x2, float y2);

public:
	BasicGame();
	void start(int nTanks);
	void step(float timeStep);
	void tank_move(int tankID, float direction);
	void tank_rotate(int tankID, float direction);
	void tank_fire(int tankID);

	void debug_draw(sf::RenderWindow &window);
};

/*

Tank.filter.categoryBits = 0x0001
Bullet.filter.categoryBits = 0x0002
Wall.filter.categoryBits = 0x0004

Tank.filter.maskBits = 0xFFFF
Bullet.filter.maskBits = 0x0005
Wall.filter.maskBits = 0xFFFF

*/
