cmake_minimum_required(VERSION 3.12)

project(Snake)

add_executable(snake
    src/main.c
    src/Game.c
    src/Renderer.c
    src/Utils.c
    src/Entities.c
)

target_include_directories(snake PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_property(TARGET snake PROPERTY C_STANDARD 11)

if (WIN32)
    target_sources(snake PRIVATE
        src/Platform/Windows/Terminal.c)
elseif(UNIX)
    target_compile_options(snake PRIVATE -fsanitize=address -Wall -Wextra -pedantic -Wpedantic)
    target_link_libraries(snake PRIVATE asan)
    target_sources(snake PRIVATE
        src/Platform/Linux/Timings.c
        src/Platform/Linux/Terminal.c
    )
endif()
