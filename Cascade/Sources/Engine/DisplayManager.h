#ifndef DIPLAY_MANAGER_H_
# define DISPLAY_MANAGER_H_

# include "SDL.h"

class DisplayManager
{
public:
	static DisplayManager & GetInstance(void)
	{
		static DisplayManager Instance;

		return Instance;
	};

	DisplayManager(DisplayManager const&) = delete;
	void operator=(DisplayManager const&) = delete;

	int m_winX;
	int m_winY;

	const char * m_winTitle = "Cascade";

	SDL_Window*		m_window;
	SDL_Renderer*	m_renderer;

private:
	DisplayManager();
};

#endif //!DISPLAY_MANAGER_H_
