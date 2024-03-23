#pragma once
#include "SDL.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	// RunLoop���Ŏg����֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// SDL�ō����E�B���h�E
	SDL_Window* mWindow;
	// �Q�[���̑��s�������t���O
	bool mIsRunning;
};
