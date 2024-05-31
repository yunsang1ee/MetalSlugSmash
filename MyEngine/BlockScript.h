#pragma once
#include "ysScript.h"
using namespace ys;
class BlockScript : public ys::Script
{
public:
	BlockScript();
	~BlockScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;

	virtual void OnCollisionEnter(Collider * other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;

private:
	float deathTime;
	float time;
};
