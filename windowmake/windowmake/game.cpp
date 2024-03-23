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
		SDL_Log("SDLを初期化できません: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Window make",
		100,	// ウィンドウ左上隅のx座標
		100,	// ウィンドウ左上隅のY座標
		1024,	// Width
		768,	// height
		SDL_WINDOW_RESIZABLE	// フラグ
	);

	if (!mWindow) {
		SDL_Log("ウィンドウの作成に失敗: %s", SDL_GetError());
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
