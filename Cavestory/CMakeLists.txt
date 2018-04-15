cmake_minimum_required(VERSION 3.10)
project(Cavestory)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Cavestory
        AnimatedSprite.cpp
        AnimatedSprite.h
        easylogging++.cc
        easylogging++.h
        Game.cpp
        Game.h
        Globals.h
        Graphics.cpp
        Graphics.h
        Input.cpp
        Input.h
        Level.cpp
        Level.h
        main.cpp
        Player.cpp
        Player.h
        Sprite.cpp
        Sprite.h
        tinyxml2.cpp
        tinyxml2.h Tile.cpp Tile.h)
target_link_libraries(Cavestory ${SDL2_LIBRARY})
target_link_libraries(Cavestory ${SDL2_IMAGE_LIBRARIES})

add_custom_command(
        TARGET Cavestory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/content
        ${CMAKE_CURRENT_BINARY_DIR}/content)

