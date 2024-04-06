#pragma once

class Component
{
public:
	// コンストラクタ
	// updateOrderが小さい順に更新
	Component(class Actor* owner, int update = 100);

	virtual ~Component();

	// コンポーネントをデルタタイムごとに更新
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
	
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};