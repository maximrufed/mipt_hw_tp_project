cmake_minimum_required(VERSION 3.16)
project(tanks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS graphics window system REQUIRED)

set(sources
    src/game.cpp
    src/tank.cpp
    src/wall.cpp
    src/classData.cpp
    src/contactListener.cpp
    src/constants.cpp
    src/bullet/bullet.cpp
    src/bullet/bulletBasicTimer.cpp
    src/bullet/bulletMine.cpp
    src/weapon/weapon.cpp
    src/weapon/weaponBullet.cpp
    src/weapon/weaponBuckshot.cpp
    src/weapon/weaponMine.cpp
    src/bonus/bonus.cpp
    src/bonus/bonusMine.cpp
    src/bonus/bonusBuckshot.cpp
    src/graphics/basic_sfml_graphics.cpp
    src/graphics/sfml_event_manager.cpp
)

add_executable(main main.cpp ${sources})

include_directories(src)
include_directories(src/weapon)
include_directories(src/bullet)
include_directories(src/bonus)
include_directories(src/graphics)

# target_include_directories(main PRIVATE src)

# link SFML
target_link_libraries(main sfml-graphics sfml-window sfml-system)

# link box2d
add_subdirectory(libs)

target_link_libraries(main box2d)
