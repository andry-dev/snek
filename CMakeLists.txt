cmake_minimum_required(VERSION 3.12)

project(Snake)

add_executable(snake
    src/main.c
    src/Game.c
    )
target_include_directories(snake PUBLIC ${PROJECT_SOURCE_DIR}/include)

