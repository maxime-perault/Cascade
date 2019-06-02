# CMakeList.txt : CMake project for Cascade, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (  SRC_PATH ./Sources/)

set (   SRC_IMGUI_SRC
        ${SRC_PATH}imgui/imgui.cpp
        ${SRC_PATH}imgui/imgui_demo.cpp
        ${SRC_PATH}imgui/imgui_draw.cpp
        ${SRC_PATH}imgui/imgui_impl_dx9.cpp
        ${SRC_PATH}imgui/imgui_impl_win32.cpp
        ${SRC_PATH}imgui/imgui_widgets.cpp

        ${SRC_PATH}imgui_sdl/imgui_sdl.cpp
)
set (   SRC_IMGUI_H
        ${SRC_PATH}imgui/imconfig.h
        ${SRC_PATH}imgui/imgui.h
        ${SRC_PATH}imgui/imgui_impl_dx9.h
        ${SRC_PATH}imgui/imgui_impl_win32.h
        ${SRC_PATH}imgui/imgui_internal.h
        ${SRC_PATH}imgui/imstb_rectpack.h
        ${SRC_PATH}imgui/imstb_textedit.h
        ${SRC_PATH}imgui/imstb_truetype.h

        ${SRC_PATH}imgui_sdl/imgui_sdl.h)

set (   SRC_ENGINE_SRC
        ${SRC_PATH}Engine/DisplayManager.cpp
)

set (   SRC_ENGINE_H
        ${SRC_PATH}Engine/DisplayManager.h
)

set (   SRC_GAME_SRC
        ${SRC_PATH}Game/GameLoop.cpp
)

set (   SRC_GAME_H
        ${SRC_PATH}Game/GameLoop.h
)

source_group("imgui")
source_group("imgui\\h"     FILES ${SRC_IMGUI_H})
source_group("imgui\\src"   FILES ${SRC_IMGUI_SRC})

source_group("Game")
source_group("Game\\h"     FILES ${SRC_GAME_H})
source_group("Game\\src"   FILES ${SRC_GAME_SRC})

source_group("Engine")
source_group("Engine\\h"     FILES ${SRC_ENGINE_H})
source_group("Engine\\src"   FILES ${SRC_ENGINE_SRC})

ADD_EXECUTABLE (Cascade
                main.cpp
                ${SRC_IMGUI_SRC}
                ${SRC_IMGUI_H}
                ${SRC_GAME_SRC}
                ${SRC_GAME_H}
                ${SRC_ENGINE_SRC}
                ${SRC_ENGINE_H})

target_link_libraries(  Cascade
                        d3d9.lib
                        $(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/x86/SDL2.lib
                        $(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/x86/SDL2main.lib)