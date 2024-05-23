#pragma once
#include "ysScript.h"
using namespace ys;
class pracPlayerScript : public Script
{
public:
	pracPlayerScript();
	~pracPlayerScript();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);

	void SetSpeed(const float& speed) { this->speed = speed; }
	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;
private:
	math::Vector2 prevPosition;
	float time = 0;
	bool goingDown;
	float speed=500;
	float coolTime;
	int count;
};

