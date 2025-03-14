

project(1fish)

add_executable(1fish main.cpp compile.cpp run.cpp)


set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -s")
set_property(TARGET 1fish PROPERTY CXX_STANDARD 20)