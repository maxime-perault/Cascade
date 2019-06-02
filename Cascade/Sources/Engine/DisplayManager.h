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

	void ClearColor(const float & r, const float & g, const float & b, const float & a);

protected:

private:
	DisplayManager();

public:
	int m_winX;
	int m_winY;

	const char * m_winTitle = "Cascade";

	SDL_Window*		m_window;
	SDL_Renderer*	m_renderer;

protected:

private:

};

#endif //!DISPLAY_MANAGER_H_
