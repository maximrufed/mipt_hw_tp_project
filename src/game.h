#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "graphics.h"

#include <iostream>
#include <random>
#include <set>
#include <memory>

#include "bonus.h"
#include "bonusBuckshot.h"
#include "bonusMine.h"
#include "box2d/box2d.h"
#include "bullet.h"
#include "bulletBasicTimer.h"
#include "bulletMine.h"
#include "classData.h"
#include "constants.h"
#include "contactListener.h"
#include "tank.h"
#include "wall.h"
#include "weapon.h"
#include "weaponBuckshot.h"
#include "weaponBullet.h"
#include "weaponMine.h"

class Graphics;

class BasicGame
{
private:
    std::shared_ptr<Graphics> graphics_;
    b2Vec2 gravity_;
    b2World world_;
    std::vector<std::shared_ptr<Tank>> tanks_;
    std::vector<Wall> walls_;
    std::vector<std::shared_ptr<Bullet>> bullets_;
    std::vector<std::shared_ptr<Bonus>> bonuses_;

    std::vector<std::string> bonusesNames_ = {"mine", "buckshot"};

    int nextTankID_ = 0;
    int nextWeaponID_ = 0;
    int nextBulletID_ = 0;

    float nextBonusTimer_ = 0;

    void addWallBetweenCells(int x1, int y1, int x2, int y2);

    void addWall(float x1, float y1, float x2, float y2);

    void initRandomMaze();

    void initTanks(int nTanks);

    void initBonuses();

    void bonusStep(float timeStep);

    std::shared_ptr<Tank> findTank(int tankID);

    void setDefaultWeaponToTank(std::shared_ptr<Tank> tank);

public:
    BasicGame(std::shared_ptr<Graphics> graphics);

    void start(int nTanks);

    void step(float timeStep);

    void tank_move(int tankID, float direction);

    void tank_rotate(int tankID, float direction);

    void tank_fire(int tankID);

    void draw();

    int getResult();
};

/*

Tank.filter.categoryBits = 0x0001
Bullet.filter.categoryBits = 0x0002
Wall.filter.categoryBits = 0x0004

Tank.filter.maskBits = 0xFFFF
Bullet.filter.maskBits = 0x0005
Wall.filter.maskBits = 0xFFFF

*/
