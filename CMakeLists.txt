cmake_minimum_required(VERSION 3.16)
project(tanks LANGUAGES CXX)

set(sources
    src/game.cpp
    src/tank.cpp
    src/wall.cpp
    src/bullet.cpp
    src/bulletBasicTimer.cpp
    src/bulletMine.cpp
    src/weapon.cpp
    src/weaponBullet.cpp
    src/weaponMine.cpp
    src/classData.cpp
    src/contactListener.cpp
    src/constants.cpp
)

add_executable(main main.cpp ${sources})

target_include_directories(main PRIVATE src)

# link SFML
target_link_libraries(main sfml-graphics sfml-window sfml-system)

# link box2d
add_subdirectory(libs)
target_link_libraries(main box2d)
