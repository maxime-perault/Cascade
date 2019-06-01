# CMakeList.txt : CMake project for Cascade, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

ADD_EXECUTABLE (Cascade
main.cpp
./Sources/imgui/imgui.cpp
./Sources/imgui/imgui_demo.cpp
./Sources/imgui/imgui_draw.cpp
./Sources/imgui/imgui_impl_dx9.cpp
./Sources/imgui/imgui_impl_win32.cpp
./Sources/imgui/imgui_widgets.cpp
./Sources/imgui_sdl/imgui_sdl.cpp)

target_link_libraries(Cascade d3d9.lib $(SolutionDir)/Cascade/Libraries/SDL2-2.0.9/lib/x86/SDL2.lib $(SolutionDir)/Cascade/Libraries/SDL2-2.0.9/lib/x86/SDL2main.lib)