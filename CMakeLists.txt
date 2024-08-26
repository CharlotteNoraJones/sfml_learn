cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME SFMLProject)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

project(${PROJECT_NAME} LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt
    GIT_TAG master)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(EnTT)

add_executable(${PROJECT_NAME} src/main.cpp)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE \W4 \WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDARD 20
CXX_STANDARD_REQUIRED YES
CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)