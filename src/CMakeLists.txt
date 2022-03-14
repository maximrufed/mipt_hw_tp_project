project(src)

add_library(lib_game game.cpp)
add_library(lib_tank tank.cpp)
add_library(lib_weapon tank.cpp)
add_library(lib_bullet tank.cpp)

target_link_libraries(lib_game lib_tank)
target_link_libraries(lib_game lib_bullet)

target_link_libraries(lib_tank lib_weapon)
target_link_libraries(lib_tank lib_bullet)

target_link_libraries(lib_weapon lib_bullet)

target_link_libraries(lib_game -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_game box2d)

target_link_libraries(lib_tank -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_tank box2d)

target_link_libraries(lib_weapon -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_weapon box2d)

target_link_libraries(lib_bullet -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(lib_bullet box2d)

# set(src lib_game lib_tank)

# target_link_libraries(game.cpp tank.cpp)

add_library(lib_src INTERFACE)
target_link_libraries(lib_src INTERFACE lib_game lib_tank lib_weapon lib_bullet)
# set_target_properties(lib_src PROPERTIES LINKER_LANGUAGE CXX)
# target_link_libraries(lib_src -lsfml-graphics -lsfml-window -lsfml-system)

