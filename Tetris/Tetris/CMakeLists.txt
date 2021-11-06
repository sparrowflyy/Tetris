cmake_minimum_required(VERSION 3.20)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(PROJECT_HEADERS
        TetrisGame/GTetris.h
        TetrisGame/TField.h
        GEvent.h
        GGame.h
        GLoop.h
        GObj.h
        GObjIntersector.h
        GUtils.h
        TetrisGame/TBackground.h TetrisGame/TWidget.h)
set(PROJECT_SOURCES
        TetrisGame/TField.cpp
        TetrisGame/GTetris.cpp
        GUtils.cpp
        GObj.cpp
        GLoop.cpp
        GObjIntersector.cpp
        TetrisGame/TBackground.cpp TetrisGame/TWidget.cpp)

add_executable(Tetris main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS} TetrisGame/TBackground.h TetrisGame/TBackground.cpp TetrisGame/TWidget.h TetrisGame/TWidget.cpp)
target_link_libraries(Tetris sfml-graphics sfml-audio)

