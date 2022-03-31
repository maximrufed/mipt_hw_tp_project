#include "weaponMine.h"

WeaponMine::WeaponMine(Tank *tank, int id)
{
    id_ = id;
    tank_ = tank;
}

std::vector<Bullet *> WeaponMine::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0)
        return {};

    std::vector<Bullet *> result;

    float angleRad = tank_->getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank_->getBody()->GetPosition();
    float length = (tank_->getSizeY() + bulletSize_) * 0.5 + 0.2;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    Bullet *bullet = new BulletMine(world, bulletSize_, pos, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank_->getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(bullet);

    nBulletsLeft_--;

    if (nBulletsLeft_ <= 0)
        alive_ = false;

    return result;
}

void WeaponMine::step(float timeStep)
{
    // nothing
}

void WeaponMine::bulletDie()
{
    // nothing
}

WeaponMine::~WeaponMine()
{
    tank_ = nullptr;
}

void WeaponMine::setTank(Tank *tank)
{
    tank_ = tank;
}

void WeaponMine::debug_draw(sf::RenderWindow &window)
{
    b2Vec2 position = tank_->getBody()->GetPosition();
    float rotation = tank_->getBody()->GetAngle();

    sf::RectangleShape rectangle(sf::Vector2f(sizeGunX_ * graphics::SCALE, sizeGunY_ * graphics::SCALE));
    rectangle.setFillColor(sf::Color(194, 178, 180, 255));
    rectangle.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
    rectangle.rotate(rotation * graphics::DEG);
    rectangle.setOrigin(sizeGunX_ * 0.5 * graphics::SCALE, sizeGunY_ * 0.5 * graphics::SCALE);
    window.draw(rectangle);
}
