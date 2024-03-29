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
	// RunLoop���Ŏg����֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// SDL�ō����E�B���h�E
	SDL_Window* mWindow;
	// �Q�[���̑��s�������t���O
	bool mIsRunning;
	// SDL�����_���[
	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;

	Vector2 mPaddlePos;
	Vector2 mBallPos;

};
