﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# avoid creating the ZERO_CHECK sub-project
set(CMAKE_SUPPRESS_REGENERATION true)

project (Cascade)

include_directories(Cascade
./Cascade/Sources
./Cascade/Sources/imgui
./Cascade/Sources/opengl
./Cascade/Sources/sdl
./Cascade/Libraries/SDL2-2.0.9/include)

# Include sub-projects.
add_subdirectory (Cascade)