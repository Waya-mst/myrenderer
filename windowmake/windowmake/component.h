#pragma once

class Component
{
public:
	// コンストラクタ
	// updateorderが小さい順に更新
	Component(class Actor* owner, int update = 100);

	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};