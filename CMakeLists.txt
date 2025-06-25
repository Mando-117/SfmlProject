cmake_minimum_required(VERSION 3.16)
project(SFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml")

find_package(SFML 3.0 REQUIRED COMPONENTS Window Graphics)

add_executable(SFMLProject main.cpp)

target_link_libraries(SFMLProject SFML::Window SFML::Graphics)