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

	// �A�N�e�B�u�ȃA�N�^�[�ւ̃|�C���^
	std::vector<class Actor*> mActors;
	// �҂���Ԃ̃A�N�^�[�ւ̃|�C���^
	std::vector<class Actor*> mPendingActors;

	bool mUpdatingActors;
};
