cmake_minimum_required(VERSION 4.3)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
add_executable(maze src/main.cc)

target_include_directories(maze PRIVATE include)
target_link_libraries(maze PRIVATE SFML::Graphics SFML::Window SFML::System)

