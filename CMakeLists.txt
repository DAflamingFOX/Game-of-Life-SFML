cmake_minimum_required(VERSION 3.28)
project(ConwaysGameOfLife LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Camera.cpp)

add_executable(main ${SOURCES})
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics)

# Copy fonts folder to build directory
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fonts
)