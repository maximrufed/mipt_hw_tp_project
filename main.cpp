#include <iostream>
#include "box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

void game() {
	b2Vec2 gravity(0.0f, -10.0f);

	b2World world(gravity);

	// create body defenition
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// create body from body_def
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);
}

int main_loop() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

// just test that libraries includes correctly

signed main() {
    game();
	main_loop();

    std::cout << "done" << std::endl;
    return 0;
}
