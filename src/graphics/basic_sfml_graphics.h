#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "game.h"
#include <numbers>
#include <stdexcept>
#include <cmath>

class Data {
private:
    sf::Texture tank_[4];
    sf::Texture weapon_[4][3];
    sf::Texture bonus_[2];

public:
    Data(const std::string&);

    sf::Sprite tank[4];
    sf::Sprite weapon[4][3];
    sf::Sprite bonus[2];
    sf::Font font;
    sf::Color tank_colors[4];
};

class BasicSfmlGraphics : public Graphics {
public:
    static constexpr float SCALE = 15;
    static constexpr float DEG = 180.0 / std::numbers::pi_v<float>;
    static constexpr float TANK_DIFF_FROM_CENTER = 21.f / 250.f;

private:
    std::shared_ptr<sf::RenderWindow> window_;
    std::shared_ptr<Data> data_;

    bool mouseInCircle(const sf::Vector2f& position, float radius);
    
public:
    BasicSfmlGraphics(std::shared_ptr<sf::RenderWindow>, const std::string&);

    bool isOpen() const override;

    int menu(int maxNumber) override;

    void clear() override;

    void draw(std::shared_ptr<Tank>) override;

    void draw(std::shared_ptr<Bullet>) override;

    void draw(std::shared_ptr<Wall>) override;

    void draw(std::shared_ptr<Bonus>) override;

    virtual void setScore(std::vector<int>) override;

    void display() override;

    void close() override;
    
    ~BasicSfmlGraphics() override;
};
