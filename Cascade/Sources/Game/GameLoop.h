#ifndef GAMELOOP_H_
# define GAMELOOP_H_


class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	const bool Events(void);

	const int Start(void);
};

#endif //!GAMELOOP_H_