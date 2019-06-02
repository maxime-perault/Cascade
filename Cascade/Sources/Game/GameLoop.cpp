#include "Game/GameLoop.h"
#include "Engine/DisplayManager.h"

#include "imgui.h"
#include "imgui_sdl.h"

#include "SDL.h"

#include <iostream>
#include <chrono>
#include <ctime>

#include <vector>

GameLoop::GameLoop()
{

}


GameLoop::~GameLoop()
{

}

const bool GameLoop::Events(void)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	int wheel = 0;

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if ((e.type == SDL_QUIT) || (e.type == SDLK_ESCAPE))
		{
			return false;
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
	io.DeltaTime = 1.0 / 60.0;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);

	return true;
}

const int GameLoop::Start(void)
{
	DisplayManager & cDM_DisplayManager = DisplayManager::GetInstance();
	bool run = true;

	std::chrono::time_point<std::chrono::steady_clock>	endTime = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock>	startTime = std::chrono::steady_clock::now();
	std::chrono::milliseconds							elapsedTime;
	std::chrono::milliseconds							totalTime(0);
	std::size_t											FPSCount = 0;
	std::size_t											CurrentFPS = 0;

	ImVec4	vClearColor		= ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (run)
	{
		run = this->Events();

		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("clear color", (float*)&vClearColor); // Edit 3 floats representing a color

		startTime = std::chrono::steady_clock::now();

		elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(startTime - endTime);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)(elapsedTime.count()), (float)FPSCount);

		endTime = startTime;

		totalTime += elapsedTime;
		++CurrentFPS;

		if (totalTime >= std::chrono::milliseconds(1000))
		{
			FPSCount = CurrentFPS;
			CurrentFPS = 0;
			totalTime = std::chrono::milliseconds(0);
		}
		
		ImGui::End();

		ImGui::EndFrame();

		cDM_DisplayManager.ClearColor(vClearColor.x, vClearColor.y, vClearColor.z, 1.f);

		std::vector<int> vec;
		vec.clear();
		for (int i(0); i < 60000; ++i)
		{
			int j = rand();
			vec.push_back(j);
		}

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		SDL_RenderPresent(cDM_DisplayManager.m_renderer);
	}

	return 0;
}