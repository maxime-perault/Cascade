# CMakeList.txt : CMake project for Cascade, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(SRC_PATH ./Sources/)

SET(IMGUI_SRC
${SRC_PATH}imgui/imgui.cpp
${SRC_PATH}imgui/imgui_demo.cpp
${SRC_PATH}imgui/imgui_draw.cpp
${SRC_PATH}imgui/imgui_tables.cpp
${SRC_PATH}imgui/imgui_widgets.cpp
${SRC_PATH}imgui/imgui_impl_sdl2.cpp
${SRC_PATH}imgui/imgui_impl_opengl3.cpp
)

SET(IMGUI_H
${SRC_PATH}imgui/imconfig.h
${SRC_PATH}imgui/imgui.h
${SRC_PATH}imgui/imgui_internal.h
${SRC_PATH}imgui/imstb_rectpack.h
${SRC_PATH}imgui/imstb_textedit.h
${SRC_PATH}imgui/imstb_truetype.h
${SRC_PATH}imgui/imgui_impl_sdl2.h
${SRC_PATH}imgui/imgui_impl_opengl3.h
${SRC_PATH}imgui/imgui_impl_opengl3_loader.h
)

source_group("Imgui")
source_group("Imgui\\src" FILES ${IMGUI_SRC})
source_group("Imgui\\h" FILES ${IMGUI_H})

ADD_EXECUTABLE (Cascade
		main.cpp
		${IMGUI_SRC}
		${IMGUI_H})

target_link_libraries(	Cascade
			opengl32.lib
			$(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/SDL2.lib
			$(SolutionDir)Cascade/Libraries/SDL2-2.0.9/lib/SDL2main.lib)