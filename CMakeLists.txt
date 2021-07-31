cmake_minimum_required(VERSION 3.17)
project(EndlessRunner)
set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES, TRUE)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)


add_executable(EndlessRunner main.cpp Player.cpp Player.h Map.cpp Map.h CONSTANTS.h Obstacle.cpp Obstacle.h ObstacleFactory.cpp ObstacleFactory.h Game.cpp Game.h Observer.cpp Observer.h Achievement.cpp Achievement.h Subject.cpp Subject.h)
target_link_libraries(EndlessRunner sfml-system sfml-window sfml-graphics sfml-audio)
