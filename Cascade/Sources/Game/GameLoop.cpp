#include "Game/GameLoop.h"
#include "Engine/DisplayManager.h"

#include "imgui.h"
#include "imgui_sdl.h"

#include "SDL.h"

GameLoop::GameLoop()
{

}


GameLoop::~GameLoop()
{

}

const int GameLoop::Start(void)
{
	const DisplayManager & cDM_DisplayManager = DisplayManager::GetInstance();
	bool run = true;

	while (run)
	{
		ImGuiIO& io = ImGui::GetIO();

		int wheel = 0;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if ((e.type == SDL_QUIT) || (e.type == SDLK_ESCAPE))
			{
				run = false;
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					io.DisplaySize.x = static_cast<float>(e.window.data1);
					io.DisplaySize.y = static_cast<float>(e.window.data2);
				}
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				wheel = e.wheel.y;
			}
		}

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

		io.DeltaTime = 1.0f / 60.0f;
		io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
		io.MouseWheel = static_cast<float>(wheel);

		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();

		SDL_SetRenderDrawColor(cDM_DisplayManager.m_renderer, 114, 144, 154, 255);
		SDL_RenderClear(cDM_DisplayManager.m_renderer);

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		SDL_RenderPresent(cDM_DisplayManager.m_renderer);
	}

	return 0;
}