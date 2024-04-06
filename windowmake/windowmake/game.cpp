#include "game.h"
#include "actor.h"

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
	, mRenderer(nullptr)
	, mTicksCount(0)
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

	mRenderer = SDL_CreateRenderer(
		mWindow, // 作成するレンダラーの描画対象になるウィンドウ
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);

	if (!mRenderer) {
		SDL_Log("failed to create renderer: %s", SDL_GetError());
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
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// SDL_QUITイベント(ウィンドウ消去)のとき、ループ終了
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// キーボードの状態を取得する
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// ECSが押されていても終了
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
}


void Game::GenerateOutput()
{
	// 描画色の設定
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);

	// バックバッファを描画色でクリア
	SDL_RenderClear(mRenderer);

	// フロントバッファとバックバッファを交換
	SDL_RenderPresent(mRenderer);

}