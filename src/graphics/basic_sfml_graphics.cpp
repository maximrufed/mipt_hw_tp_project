#include "basic_sfml_graphics.h"

Data::Data() {
    for (size_t i = 0; i < 4; ++i) {
        tank_[i].loadFromFile(std::string("../images/PNG/Hulls_Color_") + 
                static_cast<char>('A' + i) + "/Hull_06.png", sf::IntRect(50, 3, 156, 250));
        
        tank[i].setTexture(tank_[i]);
        tank[i].setOrigin(sf::Vector2f(78, 125));
        tank[i].setScale(sf::Vector2f(graphics::tankSizeX * BasicSfmlGraphics::SCALE / 156.f, 
                                      graphics::tankSizeY * BasicSfmlGraphics::SCALE / 250.f));

        weapon_[i][0].loadFromFile(std::string("../images/PNG/Weapon_Color_") + static_cast<char>('A' + i) + "/Gun_01.png");
        weapon_[i][1].loadFromFile(std::string("../images/PNG/Weapon_Color_") + static_cast<char>('A' + i) + "/Gun_07.png");
        weapon_[i][2].loadFromFile(std::string("../images/PNG/Weapon_Color_") + static_cast<char>('A' + i) + "/Gun_03_B.png");

        for (size_t j = 0; j < 3; ++j) {
            weapon[i][j].setTexture(weapon_[i][j]);
        }
        
        weapon[i][0].setOrigin(sf::Vector2f(49, 160));
        weapon[i][0].setScale(sf::Vector2f(graphics::weaponBulletSizeX * BasicSfmlGraphics::SCALE / 22.f, 
                                           graphics::weaponBulletSizeY * BasicSfmlGraphics::SCALE / 139.f));
    
        weapon[i][1].setOrigin(sf::Vector2f(43, 160));
        weapon[i][1].setScale(sf::Vector2f(graphics::weaponBuckshotSizeX * BasicSfmlGraphics::SCALE / 26.f,
                                           graphics::weaponBuckshotSizeY * BasicSfmlGraphics::SCALE / 139.f));
        
        weapon[i][2].setOrigin(sf::Vector2f(33, 43));
        weapon[i][2].setScale(sf::Vector2f(graphics::weaponMineSizeX * BasicSfmlGraphics::SCALE / 66.f,
                                           graphics::weaponMineSizeY * BasicSfmlGraphics::SCALE / 68.f));
    }

    bonus_[0].loadFromFile("../images/PNG/bonuses/buckshot.png");
    bonus_[1].loadFromFile("../images/PNG/bonuses/mine.png");

    bonus[0].setTexture(bonus_[0]);
    bonus[0].setOrigin(sf::Vector2f(50, 50));
    bonus[0].setScale(sf::Vector2f(graphics::bonusSize * BasicSfmlGraphics::SCALE / 100.f,
                                    graphics::bonusSize * BasicSfmlGraphics::SCALE / 100.f));

    bonus[1].setTexture(bonus_[1]);
    bonus[1].setOrigin(sf::Vector2f(32, 32));
    bonus[1].setScale(sf::Vector2f(graphics::bonusSize * BasicSfmlGraphics::SCALE / 64.f,
                                    graphics::bonusSize * BasicSfmlGraphics::SCALE / 64.f));

    font.loadFromFile("../data/CyrilicOld.ttf");

    tank_colors[0] = sf::Color(124, 91, 79, 255);
    tank_colors[1] = sf::Color(146, 141, 94, 255);
    tank_colors[2] = sf::Color(97, 152, 147, 255);
    tank_colors[3] = sf::Color(97, 115, 152, 255);
}

BasicSfmlGraphics::BasicSfmlGraphics(std::shared_ptr<sf::RenderWindow> window): window_(window) {}

bool BasicSfmlGraphics::isOpen() const {
    return window_->isOpen();
}

void BasicSfmlGraphics::clear() {
    window_->clear(sf::Color(255, 255, 255, 255));
}

void BasicSfmlGraphics::display() {
    window_->display();
}

void BasicSfmlGraphics::draw(std::shared_ptr<Tank> tank) {
    int id = tank->getTankID();
    sf::Sprite& tank_sprite = data_.tank[id];
    auto position = tank->getPosition();
    float rotation = tank->getRotation();
    tank_sprite.setPosition(position.x * SCALE, position.y * SCALE);
    tank_sprite.setRotation(rotation * DEG);
    window_->draw(tank_sprite);

    auto weapon = tank->getWeapon();
    int weaponID = -1;
    if (dynamic_pointer_cast<WeaponBullet, Weapon>(weapon)) {
        weaponID = 0;
    } else if (dynamic_pointer_cast<WeaponBuckshot, Weapon>(weapon)) {
        weaponID = 1;
    } else if (dynamic_pointer_cast<WeaponMine, Weapon>(weapon)) {
        weaponID = 2;
    } else {
        throw std::invalid_argument("Not supported type of weapon");
    }
    sf::Sprite& weapon_sprite = data_.weapon[id][weaponID];
    position.x -= sin(rotation) * graphics::tankSizeY * TANK_DIFF_FROM_CENTER;
    position.y += cos(rotation) * graphics::tankSizeY * TANK_DIFF_FROM_CENTER;
    weapon_sprite.setPosition(position.x * SCALE, position.y * SCALE);
    weapon_sprite.setRotation(rotation * DEG);
    window_->draw(weapon_sprite);
}

void BasicSfmlGraphics::draw(std::shared_ptr<Wall> wall) {
    auto position = wall->getPosition();
    sf::RectangleShape rectangle(sf::Vector2f(wall->getSizeX() * SCALE, wall->getSizeY() * SCALE));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOrigin(wall->getSizeX() * 0.5 * SCALE, wall->getSizeY() * 0.5 * SCALE);
    rectangle.setPosition(position.x * SCALE, position.y * SCALE);
    window_->draw(rectangle);
}

void BasicSfmlGraphics::draw(std::shared_ptr<Bullet> _bullet) {
    if (auto bullet = dynamic_pointer_cast<BulletBasicTimer, Bullet>(_bullet)) {
        auto position = bullet->getPosition();
        auto radius = bullet->getRadius();
        sf::CircleShape circle(radius * SCALE);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(position.x * SCALE, position.y * SCALE);
        circle.setOrigin(radius * SCALE, radius * SCALE);
        window_->draw(circle);
    } else if (auto bullet = dynamic_pointer_cast<BulletMine, Bullet>(_bullet)) {
        auto position = bullet->getPosition();
        float rotation = bullet->getRotation();
        sf::RectangleShape rectangle(sf::Vector2f(graphics::mineBulletSize * SCALE, graphics::mineBulletSize * SCALE));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOrigin(graphics::mineBulletSize * 0.5 * SCALE, graphics::mineBulletSize * 0.5 * SCALE);
        rectangle.setPosition(position.x * SCALE, position.y * SCALE);
        rectangle.setRotation(rotation * DEG);
        window_->draw(rectangle);
    } else {
        throw std::invalid_argument("Not supported type of bullet");
    }
}

void BasicSfmlGraphics::draw(std::shared_ptr<Bonus> bonus) {
    int id = -1;
    if (dynamic_pointer_cast<BonusBuckshot, Bonus>(bonus)) {
        id = 0;
    } else if (dynamic_pointer_cast<BonusMine, Bonus>(bonus)) {
        id = 1;
    }
    sf::Sprite& bonus_sprite = data_.bonus[id];
    auto position = bonus->getPosition();
    auto rotation = bonus->getRotation();
    bonus_sprite.setPosition(sf::Vector2f(position.x * SCALE, position.y * SCALE));
    bonus_sprite.setRotation(rotation * DEG);
    window_->draw(bonus_sprite);
}

void BasicSfmlGraphics::setScore(std::vector<int> score) {
    size_t n = score.size();
    for (size_t i = 0; i < n; ++i) {
        sf::Text text(std::to_string(score[i]), data_.font, graphics::textSize * SCALE);
        text.setFillColor(data_.tank_colors[i]);
        text.setStyle(sf::Text::Bold);
        text.setOrigin(sf::Vector2f(graphics::textSize * 0.5 * SCALE, 0));
        text.setPosition(sf::Vector2f(SCALE * graphics::wallLength * (graphics::sizeFieldX * ((0.5 + static_cast<float>(i)) / n)),
                         SCALE * graphics::wallLength * (graphics::sizeFieldY + 1)));
        window_->draw(text);
    }
}

void BasicSfmlGraphics::close() {
    window_->close();
}

BasicSfmlGraphics::~BasicSfmlGraphics() {
    close();
}