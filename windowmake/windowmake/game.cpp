#include "game.h"

Game::Game()
:mWindow(nullptr)
, mIsRunning(nullptr)
{

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂���: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Window make",
		100,	// �E�B���h�E�������x���W
		100,	// �E�B���h�E�������Y���W
		1024,	// Width
		768,	// height
		SDL_WINDOW_RESIZABLE	// �t���O
	);

	if (!mWindow) {
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s: %s", SDL_GetError());
		return false;
	}
}

void Game::RunLoop()
{
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
}
