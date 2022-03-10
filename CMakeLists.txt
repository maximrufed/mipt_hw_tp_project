project(tanks LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

add_executable(main main.cpp)

# link SFML
target_link_libraries(main -lsfml-graphics -lsfml-window -lsfml-system)

# link box2d
add_subdirectory(libs)
target_link_libraries(main box2d)
