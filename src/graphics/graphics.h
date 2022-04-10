#pragma once
#include <memory>

class Tank;
class Bullet;
class Wall;
class Bonus;

class Graphics {
public:
    virtual bool isOpen() const = 0;

    virtual void draw(std::shared_ptr<Tank>) = 0;

    virtual void draw(std::shared_ptr<Bullet>) = 0;

    virtual void draw(std::shared_ptr<Wall>) = 0;

    virtual void draw(std::shared_ptr<Bonus>) = 0;

    virtual void setScore(std::vector<int>) = 0;

    virtual void clear() = 0;

    virtual void display() = 0;

    virtual void close() = 0;

    virtual ~Graphics() = default;
};

