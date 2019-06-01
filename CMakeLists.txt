# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (Cascade)

include_directories(Cascade
./Cascade/Sources
./Cascade/Sources/imgui
./Cascade/Sources/imgui_sdl
./Cascade/Libraries/SDL2-2.0.9/include)

# Include sub-projects.
add_subdirectory (./Cascade)
