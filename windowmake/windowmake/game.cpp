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

	mRenderer = SDL_CreateRenderer(
		mWindow, // �쐬���郌���_���[�̕`��ΏۂɂȂ�E�B���h�E
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
		// SDL_QUIT�C�x���g(�E�B���h�E����)�̂Ƃ��A���[�v�I��
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// �L�[�{�[�h�̏�Ԃ��擾����
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// ECS��������Ă��Ă��I��
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
	// �`��F�̐ݒ�
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);

	// �o�b�N�o�b�t�@��`��F�ŃN���A
	SDL_RenderClear(mRenderer);

	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(mRenderer);

}