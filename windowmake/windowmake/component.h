#pragma once

class Component
{
public:
	// �R���X�g���N�^
	// updateorder�����������ɍX�V
	Component(class Actor* owner, int update = 100);

	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};