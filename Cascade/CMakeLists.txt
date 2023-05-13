# CMakeList.txt : CMake project for Cascade, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(IMGUI
./Sources/imgui/imgui.cpp
./Sources/imgui/imgui_demo.cpp
./Sources/imgui/imgui_draw.cpp
./Sources/imgui/imgui_tables.cpp
./Sources/imgui/imgui_widgets.cpp
)

SET(SDL
./Sources/sdl/imgui_impl_sdl2.cpp
)

SET(OPENGL
./Sources/opengl/imgui_impl_opengl3.cpp
)

ADD_EXECUTABLE (Cascade
main.cpp
${IMGUI}
${SDL}
${OPENGL}
)

target_link_libraries(Cascade opengl32.lib $(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/x64/SDL2.lib $(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/x64/SDL2main.lib)