#pragma once
#include "..\\MyEngine_source\\ysScript.h"
using namespace ys;
class BossSfxScript : public Script
{
public:
	BossSfxScript();
	~BossSfxScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	

	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;

	void SetBoss(GameObject* boss) { this->boss = boss; }
private:
	GameObject* boss;
};

