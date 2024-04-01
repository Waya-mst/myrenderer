#include "game.h"
#include<cmath>
#include<cstdlib>

const int thickness = 15;
const int paddleH = thickness * 5;

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

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	mBallVel.x = 200.0f;
	mBallVel.y = 235.0f;
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

	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}

	// ECS��������Ă��Ă��I��
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// deltaTime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// �������X�V
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < thickness) {
			mPaddlePos.y = thickness;
		}
		else if (mPaddlePos.y > (768.0f - (paddleH / 2.0f + thickness))) {
			mPaddlePos.y = 768.0f - (paddleH / 2.0f + thickness);
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallPos.x >= 1024.0f - thickness && mBallVel.x > 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	else if (mBallPos.y < thickness && mBallVel.y < 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	else if (mBallPos.y > 768.0f - thickness && mBallVel.y > 0.0f) {
		mBallVel.y = -mBallVel.y;
	}

	float diff = std::abs(mBallPos.y - mPaddlePos.y);
	if (
		diff <= paddleH / 2.0f &&
		mBallPos.x < mPaddlePos.x + thickness &&
		mBallPos.y < 768.0f - thickness && mBallPos.y > thickness &&
		mBallVel.x < 0.0f
		) {
		mBallVel.x *= -1;
	}

	if (mBallPos.x < mPaddlePos.x) {
		mIsRunning = false;
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

	// �����`�̐F�̎w��
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect right_wall{
		1024 - thickness,
		0,
		thickness,
		768
	};
	SDL_RenderFillRect(mRenderer, &right_wall);

	SDL_Rect bottom_wall{
		0,
		768 - thickness,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &bottom_wall);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - thickness / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	
	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(mRenderer);

}