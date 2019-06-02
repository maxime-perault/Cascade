#include "DisplayManager.h"

#include "imgui.h"
#include "imgui_sdl.h"

#include "SDL.h"

DisplayManager::DisplayManager()
{
	m_winX = 1280;
	m_winY = 720;

	SDL_Init(SDL_INIT_EVERYTHING);

	m_window	= SDL_CreateWindow(m_winTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_winX, m_winY, SDL_WINDOW_RESIZABLE);
	m_renderer	= SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(m_renderer, m_winX, m_winY);
}
