#pragma once

class Component
{
public:
	// �R���X�g���N�^
	// updateOrder�����������ɍX�V
	Component(class Actor* owner, int update = 100);

	virtual ~Component();

	// �R���|�[�l���g���f���^�^�C�����ƂɍX�V
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
	
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};