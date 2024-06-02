#pragma once
#include "ysScript.h"
using namespace ys;
class PlayerLowerBodyScript : public Script
{
public:
	enum class PlayerState
	{
		Idle, Move, Jump, Down, Slide, Attack, Damaged
	};

public:
	PlayerLowerBodyScript();
	~PlayerLowerBodyScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;

	void SetPlayerChest(GameObject* playerChest) { this->playerChest = playerChest; }
	GameObject* GetPlayerChest() { return playerChest; }
	PlayerState GetState() { return state; }

	virtual void OnCollisionEnter(class Collider* other) override;
	virtual void OnCollisionStay(class Collider* other) override;
	virtual void OnCollisionExit(class Collider* other) override;
private:
	void idle();
	void move();
	void down();
	void jump();
	void slide();
	void attack();
	void damaged();
private:
	GameObject* playerChest;
	PlayerState state;
	float speed;
};

