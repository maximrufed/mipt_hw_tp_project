#include "game.h"

BasicGame::BasicGame() : gravity_(b2Vec2(0.0f, 0.0f)), world_(gravity_)
{
}

void BasicGame::start(int nTanks)
{
    // init outside walls
    // horisontal (up & down)
    for (int x = 0; x < sizeFieldX_; ++x)
    {
        // add wall (x * cellSize, 0) -- ((x + 1) * cellSize, sizeFieldY_ * cellSize)
        addWall(x * wallLength_, 0, (x + 1) * wallLength_, 0);
        addWall(x * wallLength_, sizeFieldY_ * wallLength_, (x + 1) * wallLength_, sizeFieldY_ * wallLength_);
    }

    // vertical (up & down)
    for (int y = 0; y < sizeFieldY_; ++y)
    {
        // add wall (0, y * cellSize) -- (sizeFieldX_ * cellSize, (y + 1) * cellSize)
        addWall(0, y * wallLength_, 0, (y + 1) * wallLength_);
        addWall(sizeFieldX_ * wallLength_, y * wallLength_, sizeFieldX_ * wallLength_, (y + 1) * wallLength_);
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

        int convert(int x, int y)
        {
            return x + y * sizeFieldX_;
        };
    };

    struct twoPoints
    {
        int x1, y1, x2, y2;

        bool operator==(const twoPoints &other)
        {
            return (x1 == other.x1) && (y1 == other.y1) && (x2 == other.x2) && (y2 == other.y2);
        }
    };

    // init random
    std::random_device rd;                               // only used once to initialise (seed) engine
    std::mt19937 rng(rd());                              // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0, 10000007); // guaranteed unbiased

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

        for (auto e : walls)
        {
            if (dsu_.diff(dsu_.convert(e.x1, e.y1), dsu_.convert(e.x2, e.y2)))
            {
                wallsDiff.push_back(e);
            }
        }

        // select random wall & delete it
        int wallIndex = uni(rng) % wallsDiff.size();
        twoPoints eraseElement = wallsDiff[wallIndex];
        dsu_.merge(dsu_.convert(eraseElement.x1, eraseElement.y1), dsu_.convert(eraseElement.x2, eraseElement.y2));
        walls.erase(std::find(walls.begin(), walls.end(), eraseElement));
    }

    // now just delete some additional walls.
    int nDeleteWalls = std::max(0, (int)(0.1 * walls.size()));

    for (int i = 0; i < nDeleteWalls; i++)
    {
        int deleteIndex = uni(rng) % walls.size();
        walls.erase(walls.begin() + deleteIndex);
    }

    for (auto e : walls)
    {
        addWallBetweenCells(e.x1, e.y1, e.x2, e.y2);
    }

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
        int index = uni(rng) % freeCells.size();

        Weapon *weapon = nullptr;

        if (i | 1)
        {
            weapon = new WeaponBullet(nextWeaponID_++);
        }
        else
        {
            weapon = new WeaponMine(nextWeaponID_++);
        }

        tanks_.push_back(new Tank(world_, b2Vec2(wallLength_ * 0.5 + freeCells[index].first * wallLength_, wallLength_ * 0.5 + freeCells[index].second * wallLength_), uni(rng) % 100, weapon, nextTankID_++));

        freeCells.erase(freeCells.begin() + index);

        tanks_.back()->setColor(std::to_string(i)); // TODO remake after
    }

    // init listener
    ContactListener *listener = new ContactListener;

    world_.SetContactListener(listener);

    // TODO - delete after test
    // test for bullet
    // bullets_.push_back((new BulletBasicTimer(world_, 5, 15, b2Vec2(50, 50), 400, 0)));
}

void BasicGame::step(float timeStep)
{
    // call step for all objects
    for (size_t i = 0; i < tanks_.size(); ++i)
    {
        tanks_[i]->step(timeStep);
    }

    for (size_t i = 0; i < bullets_.size(); ++i)
    {
        bullets_[i]->step(timeStep);
    }

    // call step for world
    world_.Step(timeStep, 8, 8);

    // check for Tank death
    for (int i = 0; i < tanks_.size(); ++i)
    {
        if (tanks_[i]->isDead())
        {
            // std::cout << "tank number " << i << " is dead" << std::endl;
            tanks_[i]->destroy(world_);
            tanks_.erase(tanks_.begin() + i);
            i--;
        }
    }

    // check for Bullet death
    for (int i = 0; i < bullets_.size(); ++i)
    {
        if (bullets_[i]->isDead())
        {
            // say tank & weapon that bullet was killed
            // TODO
            // find tank & id & give him weaponID
            int tankID = bullets_[i]->getTankID();
            int weaponID = bullets_[i]->getWeaponID();
            for (int i = 0; i < tanks_.size(); ++i)
            {
                if (tanks_[i]->getTankID() == tankID)
                {
                    tanks_[i]->bulletDie(weaponID);
                    break;
                }
            }
            bullets_[i]->destroy(world_);

            delete bullets_[i];
            bullets_.erase(bullets_.begin() + i);
            i--;
        }
    }

    // check for Bonux death
    // TODO
}

void BasicGame::tank_move(int tankID, float direction)
{
    if (tankID < tanks_.size())
        tanks_[tankID]->move(direction);
}

void BasicGame::tank_rotate(int tankID, float direction)
{
    if (tankID < tanks_.size())
        tanks_[tankID]->rotate(direction);
}

void BasicGame::tank_fire(int tankID)
{
    if (tankID < tanks_.size())
    {
        std::vector<Bullet *> bulletsAdd = tanks_[tankID]->fire(world_, nextBulletID_);
        for (auto e : bulletsAdd)
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

    // window.display();
    // TODO - return back
}

void BasicGame::addWall(float x1, float y1, float x2, float y2)
{
    if (y1 == y2)
    {
        // horisontal wall
        y1 -= wallWidth_ * 0.5;
        y2 += wallWidth_ * 0.5;
        walls_.push_back(Wall(world_, b2Vec2(x1, y1), b2Vec2(x2, y2)));
    }
    else
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
    }
    else
    {
        // horisontal wall
        addWall(x1 * wallLength_, y2 * wallLength_, (x1 + 1) * wallLength_, y2 * wallLength_);
    }
}

int BasicGame::result()
{
    if (tanks_.size() >= 2)
    {
        return 0;
    }
    else if (tanks_.size() == 0)
    {
        return 3;
    }
    else if (tanks_.size() == 1)
    {
        return tanks_[0]->getTankID() + 1;
    }
}
