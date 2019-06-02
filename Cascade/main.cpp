#include "SDL.h"
#undef main

#include "imgui.h"
#include "imgui_sdl.h"

#include "Game/GameLoop.h"
#include "Engine/DisplayManager.h"

int main()
{
	GameLoop cGL_GameLoop;

	cGL_GameLoop.Start();

	const DisplayManager & cDM_DisplayManager = DisplayManager::GetInstance();

	ImGuiSDL::Deinitialize();

	SDL_DestroyRenderer(cDM_DisplayManager.m_renderer);
	SDL_DestroyWindow(cDM_DisplayManager.m_window);

	ImGui::DestroyContext();

	return 0;
}