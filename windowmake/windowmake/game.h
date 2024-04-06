#pragma once
#include "SDL.h"
#include<vector>

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
	void AddActor(class Actor* actor);
	
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

	// アクティブなアクターへのポインタ
	std::vector<class Actor*> mActors;
	// 待ち状態のアクターへのポインタ
	std::vector<class Actor*> mPendingActors;

	bool mUpdatingActors;
};
