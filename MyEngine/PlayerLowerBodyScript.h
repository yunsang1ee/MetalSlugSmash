#pragma once
#include "ysScript.h"
using namespace ys;
class PlayerLowerBodyScript : public Script
{

public:
	PlayerLowerBodyScript();
	~PlayerLowerBodyScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;

	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;
};

