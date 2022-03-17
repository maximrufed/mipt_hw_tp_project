project(src)

add_library(lib_game game.cpp)
add_library(lib_tank tank.cpp)
add_library(lib_wall wall.cpp)
add_library(lib_bullet bullet.cpp)
add_library(lib_bulletBasicTimer bulletBasicTimer.cpp)
add_library(lib_weapon weapon.cpp)
add_library(lib_weaponBullet weaponBullet.cpp)
add_library(lib_classData classData.cpp)
add_library(lib_contactListener contactListener.cpp)

target_link_libraries(lib_weaponBullet lib_bulletBasicTimer)
target_link_libraries(lib_weapon lib_bullet)
target_link_libraries(lib_bullet lib_weapon)
target_link_libraries(lib_tank lib_bullet)
target_link_libraries(lib_contactListener lib_game)
target_link_libraries(lib_game lib_contactListener)
target_link_libraries(lib_game lib_tank)
target_link_libraries(lib_game lib_weaponBullet)
target_link_libraries(lib_game lib_wall)
target_link_libraries(lib_bulletBasicTimer lib_bullet)

# target_link_libraries(lib_game lib_tank)
# target_link_libraries(lib_game lib_bullet)

# target_link_libraries(lib_tank lib_weapon)
# target_link_libraries(lib_tank lib_bullet)

# target_link_libraries(lib_weapon lib_bullet)

target_link_libraries(lib_game -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_game box2d)

target_link_libraries(lib_tank -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_tank box2d)

target_link_libraries(lib_wall -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_wall box2d)

target_link_libraries(lib_bullet -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_bullet box2d)

target_link_libraries(lib_bulletBasicTimer -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_bulletBasicTimer box2d)

target_link_libraries(lib_weapon -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_weapon box2d)

target_link_libraries(lib_weaponBullet -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_weaponBullet box2d)

target_link_libraries(lib_classData -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_classData box2d)

target_link_libraries(lib_contactListener -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_contactListener box2d)


# -----------------------------------------------------------------------------------------------

add_library(lib_src INTERFACE)
target_link_libraries(lib_src INTERFACE lib_game lib_tank lib_wall lib_bullet lib_bulletBasicTimer lib_weapon lib_weaponBullet lib_classData lib_contactListener)

# set_target_properties(lib_src PROPERTIES LINKER_LANGUAGE CXX)
