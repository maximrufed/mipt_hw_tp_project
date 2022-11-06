#include "event_manager.h"
#include <SFML/Graphics.hpp>

class SfmlEventManager: public EventManager {
private:
    std::shared_ptr<sf::RenderWindow> window_;
    std::shared_ptr<BasicGame> game_;

public:
    SfmlEventManager(std::shared_ptr<sf::RenderWindow>);

    void input() override;

    void setGame(std::shared_ptr<BasicGame>) override;

    ~SfmlEventManager() override = default;
};
