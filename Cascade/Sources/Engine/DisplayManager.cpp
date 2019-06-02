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

void DisplayManager::ClearColor(const float & r, const float & g, const float & b, const float & a)
{
	SDL_SetRenderDrawColor(	m_renderer,
							static_cast<Uint8>(r * 255.f),
							static_cast<Uint8>(g * 255.f),
							static_cast<Uint8>(b * 255.f),
							static_cast<Uint8>(a * 255.f));

	SDL_RenderClear(m_renderer);
}