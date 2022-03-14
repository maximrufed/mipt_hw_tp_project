project(tanks LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

add_executable(main main.cpp)

#link src
add_subdirectory(src)
# target_link_libraries(lib_src -lsfml-graphics -lsfml-window -lsfml-system)
# target_link_libraries(lib_src box2d)
# target_include_directories(lib_src .)
target_link_libraries(main lib_src)

# link SFML
target_link_libraries(main -lsfml-graphics -lsfml-window -lsfml-system)


# link box2d
add_subdirectory(libs)
target_link_libraries(main box2d)
