#include "game.h"

BasicGame::BasicGame(std::shared_ptr<Graphics> graphics) : graphics_(graphics), gravity_(b2Vec2(0.0f, 0.0f)), world_(gravity_)
{
}

void BasicGame::initRandomMaze() {
    // init outside walls
    // horisontal (up & down)
    for (int x = 0; x < graphics::sizeFieldX; ++x)
    {
        // add wall (x * cellSize, 0) -- ((x + 1) * cellSize, graphics::sizeFieldY * cellSize)
        addWall(x * graphics::wallLength, 0, (x + 1.f) * graphics::wallLength, 0);
        addWall(x * graphics::wallLength, graphics::sizeFieldY * graphics::wallLength, (x + 1.f) * graphics::wallLength, graphics::sizeFieldY * graphics::wallLength);
    }
    // vertical (up & down)
    for (int y = 0; y < graphics::sizeFieldY; ++y)
    {
        // add wall (0, y * cellSize) -- (graphics::sizeFieldX * cellSize, (y + 1) * cellSize)
        addWall(0, y * graphics::wallLength, 0, (y + 1.f) * graphics::wallLength);
        addWall(graphics::sizeFieldX * graphics::wallLength, y * graphics::wallLength, graphics::sizeFieldX * graphics::wallLength, (y + 1.f) * graphics::wallLength);
    }

    // init inside walls
    // Disjoint Set Union - algorithm
    class dsu {
       private:
        std::vector<int> d;
        int sizeFieldX_;

       public:
        dsu(int n, int sizeFieldX_) : sizeFieldX_(sizeFieldX_) {
            d.assign(n, 0);
            for (int i = 0; i < n; i++)
                d[i] = i;
        }

        int get(int a) {
            if (d[a] == a)
                return a;
            else
                return d[a] = get(d[a]);
        }

        void merge(int a, int b) {
            d[get(a)] = get(b);
        }

        bool diff(int a, int b) {
            return get(a) != get(b);
        }

        int convert(int x, int y) const {
            return x + y * sizeFieldX_;
        };
    };


    struct twoPoints
    {
        int x1, y1, x2, y2;

        bool operator==(const twoPoints& other) const {
            return (x1 == other.x1) && (y1 == other.y1) && (x2 == other.x2) && (y2 == other.y2);
        }
    };

    // list of all walls
    std::vector<twoPoints> walls;
    for (int x = 0; x < graphics::sizeFieldX; ++x)
    {
        for (int y = 0; y < graphics::sizeFieldY; ++y)
        {
            if (x + 1 < graphics::sizeFieldX)
                walls.emplace_back(twoPoints({x, y, x + 1, y}));
            if (y + 1 < graphics::sizeFieldY)
                walls.emplace_back(twoPoints({x, y, x, y + 1}));
        }
    }

    // each iter we delete a wall && merge 2 rooms
    dsu dsu_(graphics::sizeFieldX * graphics::sizeFieldY, graphics::sizeFieldX);
    for (int iter = 0; iter < graphics::sizeFieldX * graphics::sizeFieldY - 1; ++iter)
    {
        std::vector<twoPoints> wallsDiff;

        for (auto e : walls) {
            if (dsu_.diff(dsu_.convert(e.x1, e.y1), dsu_.convert(e.x2, e.y2))) {
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
    int nDeleteWalls = std::max(0, (int)(0.1 * walls.size()));

    for (int i = 0; i < nDeleteWalls; i++) {
        int deleteIndex = math::getRand() % walls.size();
        walls.erase(walls.begin() + deleteIndex);
    }

    for (auto e : walls) {
        addWallBetweenCells(e.x1, e.y1, e.x2, e.y2);
    }
}

void BasicGame::initTanks(int nTanks) {
    std::vector<std::pair<int, int>> freeCells;
    for (int x = 0; x < graphics::sizeFieldX; ++x)
    {
        for (int y = 0; y < graphics::sizeFieldY; ++y)
        {
            freeCells.emplace_back(std::make_pair(x, y));
        }
    }

    // init tanks
    for (size_t i = 0; i < nTanks; ++i) {
        int index = math::getRand() % freeCells.size();
        auto currentTank = std::make_shared<Tank>(
            world_, b2Vec2(graphics::wallLength * 0.5 + freeCells[index].first * 
                            graphics::wallLength, graphics::wallLength * 0.5 + freeCells[index].second * graphics::wallLength),
                                     math::getRand() % 100, nextTankID_++);

        setDefaultWeaponToTank(currentTank);
        freeCells.erase(freeCells.begin() + index);

        tanks_.push_back(currentTank);
        // std::cout << "tank " << i << " = " << currentTank << std::endl;
    }
}

void BasicGame::initBonuses() {
    nextBonusTimer_ = 5 + math::getRand() % 5;
}

void BasicGame::start(int nTanks) {
    initRandomMaze();
    initTanks(nTanks);
    initBonuses();

    // init collision listener
    auto* listener = new ContactListener();
    world_.SetContactListener(listener);
}

void BasicGame::bonusStep(float timeStep) {
    nextBonusTimer_ -= timeStep;

    if (nextBonusTimer_ <= 0) {
        nextBonusTimer_ = 3 + math::getRand() % 3;

        // generate random bonus
        b2Vec2 position(graphics::wallLength * (0.5 + math::getRand() % graphics::sizeFieldX),
                        graphics::wallLength * (0.5 + math::getRand() % graphics::sizeFieldY));

        float rotation = math::getRand() % 100;

        // choose random bonus
        std::string bonusName = bonusesNames_[rand() % bonusesNames_.size()];

        std::shared_ptr<Bonus> bonus;

        if (bonusName == "mine")
        {
            bonus = std::make_shared<BonusMine>(world_, position, rotation, &nextWeaponID_);
        }
        else if (bonusName == "buckshot")
        {
            bonus = std::make_shared<BonusBuckshot>(world_, position, rotation, &nextWeaponID_);
        }
        else
        {
            std::cerr << "bonus " << bonusName << " wasn't found" << std::endl;
        }

        if (bonus)
        {
            bonuses_.push_back(bonus);
        }
    }
}

void BasicGame::setDefaultWeaponToTank(std::shared_ptr<Tank> tank)
{
    // weapon = new WeaponBuckshot(tank, nextWeaponID_++);
    auto weapon = std::make_shared<WeaponBullet>(world_, tank, nextWeaponID_++);
    // weapon = new WeaponMine(currentTank, nextWeaponID_++);
    tank->setWeapon(weapon);
}

void BasicGame::step(float timeStep)
{

    // call step for all objects
    for (auto &tank : tanks_)
    {
        tank->step(timeStep);
    }

    for (auto &bullet : bullets_)
    {
        bullet->step(timeStep);
    }

    for (auto &bonus : bonuses_)
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

            // std::cout << "delete bullet " << bullets_[i] << std::endl;
            bullets_.erase(bullets_.begin() + i);
            --i;
        }
    }

    for (int i = 0; i < bonuses_.size(); ++i)
    {
        if (bonuses_[i]->isDead())
        {
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
    world_.Step(timeStep, 8, 3);
}

void BasicGame::tank_move(int tankID, float direction)
{
    auto tank = findTank(tankID);
    if (tank)
        tank->move(direction);
}

void BasicGame::tank_rotate(int tankID, float direction)
{
    auto tank = findTank(tankID);
    if (tank)
        tank->rotate(direction);
}

void BasicGame::tank_fire(int tankID)
{
    auto tank = findTank(tankID);
    if (tank)
    {
        for (auto& e : tank->fire(world_, nextBulletID_))
        {
            bullets_.push_back(std::move(e));
        }
    }
}

void BasicGame::draw()
{
    graphics_->clear();
    // main draw
    for (size_t i = 0; i < tanks_.size(); ++i)
    {
        graphics_->draw(tanks_[i]);
    }
    for (size_t i = 0; i < walls_.size(); ++i)
    {
        graphics_->draw(std::shared_ptr<Wall>(std::shared_ptr<Wall>(), &walls_[i]));
    }
    for (size_t i = 0; i < bullets_.size(); ++i)
    {
        graphics_->draw(bullets_[i]);
    }

    for (size_t i = 0; i < bonuses_.size(); ++i)
    {
        graphics_->draw(bonuses_[i]);
    }

    // graphics_->display();
}

void BasicGame::addWall(float x1, float y1, float x2, float y2) {
    if (y1 == y2) {
        // horizontal wall
        y1 -= graphics::wallWidth * 0.5;
        y2 += graphics::wallWidth * 0.5;
        walls_.push_back(Wall(world_, b2Vec2(x1, y1), b2Vec2(x2, y2)));
    } else {
        // vertical wall
        x1 -= graphics::wallWidth * 0.5;
        x2 += graphics::wallWidth * 0.5;
        walls_.push_back(Wall(world_, b2Vec2(x1, y1), b2Vec2(x2, y2)));
    }
}

void BasicGame::addWallBetweenCells(int x1, int y1, int x2, int y2) {
    if (y1 == y2) {
        // vertical wall
        addWall(x2 * graphics::wallLength, y1 * graphics::wallLength, x2 * graphics::wallLength, (y1 + 1) * graphics::wallLength);
    }
    else
    {
        // horizontal wall
        addWall(x1 * graphics::wallLength, y2 * graphics::wallLength, (x1 + 1) * graphics::wallLength, y2 * graphics::wallLength);
    }
}

int BasicGame::getResult()
{
    if (tanks_.size() >= 2)
    {
        return 0; // game is still going
    }
    else if (tanks_.size() == 0)
    {
        return -1; // toe
    }
    else
    {
        return tanks_[0]->getTankID() + 1; // tank number x wins
    }
}

std::shared_ptr<Tank> BasicGame::findTank(int tankID)
{
    for (int i = 0; i < tanks_.size(); ++i)
    {
        if (tanks_[i]->getTankID() == tankID)
        {
            return tanks_[i];
        }
    }
    return std::shared_ptr<Tank>();
}
