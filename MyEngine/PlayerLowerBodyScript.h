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
	void setPlayerChest(GameObject* playerChest) { this->playerChest = playerChest; }

	virtual void OnCollisionEnter(class Collider* other) override;
	virtual void OnCollisionStay(class Collider* other) override;
	virtual void OnCollisionExit(class Collider* other) override;
private:
	GameObject* playerChest;
};

