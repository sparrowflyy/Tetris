cmake_minimum_required(VERSION 3.20)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
#add_executable(Tetris main.cpp)
set(PROJECT_HEADERS
        TetrisGame/GTetris.h
        TetrisGame/TShape.h
        TetrisGame/TField.h
        GEvent.h
        GGame.h
        GLoop.h
        GObj.h
        GObjIntersector.h
        GUtils.h
        )
set(PROJECT_SOURCES
        TetrisGame/TField.cpp
        TetrisGame/GTetris.cpp
        GUtils.cpp
        GObj.cpp
        GLoop.cpp
        GObjIntersector.cpp
        TetrisGame/TShape.cpp
        )

add_executable(Tetris main.cpp ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(Tetris sfml-graphics sfml-audio)

