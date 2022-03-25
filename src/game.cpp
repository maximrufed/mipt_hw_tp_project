#include "game.h"

BasicGame::BasicGame() : gravity_(b2Vec2(0.0f, 0.0f)), world_(gravity_)
{
}

void BasicGame::initRandomMaze()
{
    // init outside walls
    // horisontal (up & down)
    for (int x = 0; x < sizeFieldX_; ++x)
    {
        // add wall (x * cellSize, 0) -- ((x + 1) * cellSize, sizeFieldY_ * cellSize)
        addWall(x * wallLength_, 0, (x + 1.f) * wallLength_, 0);
        addWall(x * wallLength_, sizeFieldY_ * wallLength_, (x + 1.f) * wallLength_, sizeFieldY_ * wallLength_);
    }
    // vertical (up & down)
    for (int y = 0; y < sizeFieldY_; ++y)
    {
        // add wall (0, y * cellSize) -- (sizeFieldX_ * cellSize, (y + 1) * cellSize)
        addWall(0, y * wallLength_, 0, (y + 1.f) * wallLength_);
        addWall(sizeFieldX_ * wallLength_, y * wallLength_, sizeFieldX_ * wallLength_, (y + 1.f) * wallLength_);
    }

    // init inside walls
    class dsu
    {
    private:
        std::vector<int> d;
        int sizeFieldX_;

    public:
        dsu(int n, int sizeFieldX_) : sizeFieldX_(sizeFieldX_)
        {
            d.assign(n, 0);
            for (int i = 0; i < n; i++)
                d[i] = i;
        }

        int get(int a)
        {
            if (d[a] == a)
                return a;
            else
                return d[a] = get(d[a]);
        }

        void merge(int a, int b)
        {
            d[get(a)] = get(b);
        }

        bool diff(int a, int b)
        {
            return get(a) != get(b);
        }

        int convert(int x, int y) const
        {
            return x + y * sizeFieldX_;
        };
    };

    struct twoPoints
    {
        int x1, y1, x2, y2;

        bool operator==(const twoPoints &other) const
        {
            return (x1 == other.x1) && (y1 == other.y1) && (x2 == other.x2) && (y2 == other.y2);
        }
    };

    // list of all walls
    std::vector<twoPoints> walls;
    for (int x = 0; x < sizeFieldX_; ++x)
    {
        for (int y = 0; y < sizeFieldY_; ++y)
        {
            if (x + 1 < sizeFieldX_)
                walls.emplace_back(twoPoints({x, y, x + 1, y}));
            if (y + 1 < sizeFieldY_)
                walls.emplace_back(twoPoints({x, y, x, y + 1}));
        }
    }

    // each iter we delete a wall && merge 2 rooms
    dsu dsu_(sizeFieldX_ * sizeFieldY_, sizeFieldX_);
    for (int iter = 0; iter < sizeFieldX_ * sizeFieldY_ - 1; ++iter)
    {
        std::vector<twoPoints> wallsDiff;

        for (auto e: walls)
        {
            if (dsu_.diff(dsu_.convert(e.x1, e.y1), dsu_.convert(e.x2, e.y2)))
            {
                wallsDiff.push_back(e);
            }
        }

        // select random wall & delete it
        int wallIndex = math::getRand() % static_cast<int>(wallsDiff.size());
        twoPoints eraseElement = wallsDiff[wallIndex];
        dsu_.merge(dsu_.convert(eraseElement.x1, eraseElement.y1), dsu_.convert(eraseElement.x2, eraseElement.y2));
        walls.erase(std::find(walls.begin(), walls.end(), eraseElement));
    }

    // now just delete some additional walls.
    int nDeleteWalls = std::max(0, (int) (0.1 * walls.size()));

    for (int i = 0; i < nDeleteWalls; i++)
    {
        int deleteIndex = math::getRand() % walls.size();
        walls.erase(walls.begin() + deleteIndex);
    }

    for (auto e: walls)
    {
        addWallBetweenCells(e.x1, e.y1, e.x2, e.y2);
    }
}

void BasicGame::initTanks(int nTanks)
{
    std::vector<std::pair<int, int>> freeCells;
    for (int x = 0; x < sizeFieldX_; ++x)
    {
        for (int y = 0; y < sizeFieldY_; ++y)
        {
            freeCells.emplace_back(std::make_pair(x, y));
        }
    }

    // init tanks
    for (size_t i = 0; i < nTanks; ++i)
    {
        int index = math::getRand() % freeCells.size();
        Tank *currentTank = new Tank(world_, b2Vec2(wallLength_ * 0.5 + freeCells[index].first * wallLength_,
                                                    wallLength_ * 0.5 + freeCells[index].second * wallLength_),
                                     math::getRand() % 100, nextTankID_++);

        setDefaultWeaponToTank(currentTank);
        freeCells.erase(freeCells.begin() + index);
        currentTank->setColor(std::to_string(i)); // TODO remake after

        tanks_.push_back(currentTank);
        std::cout << "tank " << i << " = " << currentTank << std::endl;

    }
}

void BasicGame::initBonuses()
{
    nextBonusTimer_ = 3 + math::getRand() % 3;
}

void BasicGame::start(int nTanks)
{
    initRandomMaze();

    initTanks(nTanks);

    initBonuses();

    // init collision listener
    auto *listener = new ContactListener();
    world_.SetContactListener(listener);
}

void BasicGame::bonusStep(float timeStep)
{
    nextBonusTimer_ -= timeStep;

    if (nextBonusTimer_ <= 0)
    {
        nextBonusTimer_ = 3 + math::getRand() % 3;

        // generate random bonus
        b2Vec2 position(wallLength_ * (0.5 + math::getRand() % sizeFieldX_),
                        wallLength_ * (0.5 + math::getRand() % sizeFieldY_));
        Bonus *bonus = new BonusMine(world_, position, math::getRand() % 100, &nextWeaponID_); // TODO
        bonuses_.push_back(bonus);
    }
}

void BasicGame::setDefaultWeaponToTank(Tank *tank)
{
    Weapon *weapon = nullptr;
    weapon = new WeaponBuckshot(world_, tank, nextWeaponID_++);
//    weapon = new WeaponBullet(world_, tank, nextWeaponID_++);
    // weapon = new WeaponMine(currentTank, nextWeaponID_++);
    tank->setWeapon(weapon);
    weapon = nullptr;
}

void BasicGame::step(float timeStep)
{

    // call step for all objects
    for (auto &tank: tanks_)
    {
        tank->step(timeStep);
    }

    for (auto &bullet: bullets_)
    {
        bullet->step(timeStep);
    }

    for (auto &bonus: bonuses_)
    {
        bonus->step(timeStep);
    }

    // step for bonus factory
    bonusStep(timeStep);

    // check for death for all objects
    // check for Tank death
    for (int i = 0; i < tanks_.size(); ++i)
    {
        if (tanks_[i]->isDead())
        {
            delete tanks_[i];
            tanks_.erase(tanks_.begin() + i);
            --i;
        }
    }

    // check for Bullet death
    for (int i = 0; i < bullets_.size(); ++i)
    {
        if (bullets_[i]->isDead())
        {
            // say tank & weapon that bullet was killed
            int tankID = bullets_[i]->getTankID();
            int weaponID = bullets_[i]->getWeaponID();
            for (int j = 0; j < tanks_.size(); ++j)
            {
                if (tanks_[j]->getTankID() == tankID)
                {
                    tanks_[j]->bulletDie(weaponID);
                    break;
                }
            }

            std::cout << "delete bullet " << bullets_[i] << std::endl;
            delete bullets_[i];
            bullets_.erase(bullets_.begin() + i);
            --i;
        }
    }

    for (int i = 0; i < bonuses_.size(); ++i)
    {
        if (bonuses_[i]->isDead())
        {
            delete bonuses_[i];
            bonuses_.erase(bonuses_.begin() + i);
            --i;
        }
    }

    for (int i = 0; i < tanks_.size(); ++i)
    {
        if (tanks_[i]->isWeaponDead())
        {
            setDefaultWeaponToTank(tanks_[i]);
        }
    }


    // call step for world
    world_.Step(timeStep, 1, 1);

}

void BasicGame::tank_move(int tankID, float direction)
{
    Tank *tank = findTank(tankID);
    if (tank != nullptr)
        tank->move(direction);
}

void BasicGame::tank_rotate(int tankID, float direction)
{
    Tank *tank = findTank(tankID);
    if (tank != nullptr)
        tank->rotate(direction);
}

void BasicGame::tank_fire(int tankID)
{
    Tank *tank = findTank(tankID);
    if (tank != nullptr)
    {
        for (auto e: tanks_[tankID]->fire(world_, nextBulletID_))
        {
            bullets_.push_back(e);
        }
    }
}

void BasicGame::debug_draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(255, 255, 255, 255));

    // main draw
    for (size_t i = 0; i < tanks_.size(); ++i)
    {
        tanks_[i]->debug_draw(window);
    }

    for (size_t i = 0; i < walls_.size(); ++i)
    {
        walls_[i].debug_draw(window);
    }

    for (size_t i = 0; i < bullets_.size(); ++i)
    {
        bullets_[i]->debug_draw(window);
    }

    for (size_t i = 0; i < bonuses_.size(); ++i)
    {
        bonuses_[i]->debug_draw(window);
    }

    // window.display();
    // TODO - return back
}

void BasicGame::addWall(float x1, float y1, float x2, float y2)
{
    if (y1 == y2)
    {
        // horizontal wall
        y1 -= wallWidth_ * 0.5;
        y2 += wallWidth_ * 0.5;
        walls_.push_back(Wall(world_, b2Vec2(x1, y1), b2Vec2(x2, y2)));
    } else
    {
        // vertical wall
        x1 -= wallWidth_ * 0.5;
        x2 += wallWidth_ * 0.5;
        walls_.push_back(Wall(world_, b2Vec2(x1, y1), b2Vec2(x2, y2)));
    }
}

void BasicGame::addWallBetweenCells(int x1, int y1, int x2, int y2)
{
    if (y1 == y2)
    {
        // vertical wall
        addWall(x2 * wallLength_, y1 * wallLength_, x2 * wallLength_, (y1 + 1) * wallLength_);
    } else
    {
        // horizontal wall
        addWall(x1 * wallLength_, y2 * wallLength_, (x1 + 1) * wallLength_, y2 * wallLength_);
    }
}

int BasicGame::getResult()
{
    if (tanks_.size() >= 2)
    {
        return 0; // game is still going
    } else if (tanks_.size() == 0)
    {
        return -1; // toe
    } else if (tanks_.size() == 1)
    {
        return tanks_[0]->getTankID() + 1; // tank number x wins
    }
}

Tank *BasicGame::findTank(int tankID)
{
    for (int i = 0; i < tanks_.size(); ++i)
    {
        if (tanks_[i]->getTankID() == tankID)
        {
            return tanks_[i];
        }
    }
    return nullptr;
}
