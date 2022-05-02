#include <memory>
#include "game.h"

class EventManager {
public:
    virtual void input() = 0;
    virtual void setGame(std::shared_ptr<BasicGame>) = 0;
    virtual ~EventManager() = default;
};
