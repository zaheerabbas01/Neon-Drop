cmake_minimum_required(VERSION 3.28)

project(MyGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_executable(MyGame
    src/main.cpp
    src/Game.cpp
)

target_compile_features(MyGame PRIVATE cxx_std_20)

target_link_libraries(MyGame PRIVATE
    SFML::Graphics
)