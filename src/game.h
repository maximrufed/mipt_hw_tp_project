#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>
#include <vector>
#include <string>

#include "tank.h"
#include "bullet.h"

class Game
{
public:
	virtual void start() = 0;
	virtual void step(float timeStep) = 0;
	virtual void tank_move(int tankID, float direction) = 0;
	virtual void tank_rotate(int tankID, float direction) = 0;
	virtual void tank_fire() = 0;
};

class BasicGame : public Game
{
private:
	b2Vec2 gravity_;
	b2World world_;
	std::vector<Tank> tanks_;
	// std::vector<Bullet> bullets_;
	// std::vector<Wall> walls_;
	// std::vector<Bonus> bonuses_;

public:
	BasicGame(int nTanks);
	void start() override;
	void step(float timeStep) override;
	void tank_move(int tankID, float direction) override;
	void tank_rotate(int tankID, float direction) override;
	void tank_fire() override;

	void debug_draw(sf::RenderWindow &window);
};
