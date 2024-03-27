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

	// コンストラクタとデストラクタ
	Actor(class Game* game);
	virtual ~Actor();

	// ゲームから呼び出される更新関数
	void Update(float deltaTime);

	// アクターが持つ全コンポーネントを更新
	void UpdateComponents(float deltaTime);

	// アクター独自の更新処理
	virtual void UpdateActor(float deltaTime);

	// コンポーネントの追加、削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// アクターの状態
	State mState;

	// 座標変換
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// アクターのコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
};