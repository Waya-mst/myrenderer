#pragma once
#include "SDL.h"
#include "game.h"
#include <vector>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	// �R���X�g���N�^�ƃf�X�g���N�^
	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����X�V�֐�
	void Update(float deltaTime);

	// �A�N�^�[�����S�R���|�[�l���g���X�V
	void UpdateComponents(float deltaTime);

	// �A�N�^�[�Ǝ��̍X�V����
	virtual void UpdateActor(float deltaTime);

	// �R���|�[�l���g�̒ǉ��A�폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// �A�N�^�[�̏��
	State mState;

	// ���W�ϊ�
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// �A�N�^�[�̃R���|�[�l���g
	std::vector<class Component*> mComponents;
	class Game* mGame;
};