cmake_minimum_required(VERSION 3.12)

project(Snake)

add_executable(snake
    src/main.c
    src/Game.c
    src/Renderer.c
    )
target_include_directories(snake PUBLIC ${PROJECT_SOURCE_DIR}/include)


if (WIN32)
    target_sources(snake PRIVATE src/input/windows.c)
elseif(UNIX)
    target_sources(snake PRIVATE src/input/nix.c)
endif()
