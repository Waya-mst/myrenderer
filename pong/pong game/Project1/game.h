#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	// RunLoop内で使われる関数
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// SDLで作られるウィンドウ
	SDL_Window* mWindow;
	// ゲームの続行を示すフラグ
	bool mIsRunning;
	// SDLレンダラー
	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;

	Vector2 mPaddlePos;
	Vector2 mBallPos;

};
