cmake_minimum_required(VERSION 3.16)
project(MiniEngine VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG QUIET)
if(NOT TARGET SDL2::SDL2)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
endif()

add_executable(MiniEngine
    src/main.cpp
    src/Engine.cpp
    src/Enemy.cpp
    src/Player.cpp
    src/GameObject.cpp
    src/TextureManager.cpp
)
target_include_directories(MiniEngine PRIVATE include)
if(TARGET SDL2::SDL2)
    target_link_libraries(MiniEngine PRIVATE SDL2::SDL2)
else()
    target_link_libraries(MiniEngine PRIVATE PkgConfig::SDL2)
endif()

add_custom_command(TARGET MiniEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:MiniEngine>/assets")
